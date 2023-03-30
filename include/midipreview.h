#ifndef MIDIPREVIEW_H
#define MIDIPREVIEW_H

#include <vector>
#include <deque>
#include <set>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "Options.h"
#include "MidiFile.h"

#include "brutedefinitions.h"

// #define TSF_IMPLEMENTATION
// #include "tsf.h"

typedef std::tuple< int64_t, int64_t, int64_t, int, int, float > ToneTuple;

class MidiPreview
{
public:
   std::vector< smf::MidiFile > PreviewMidiTracks; // this stores the preview midis of the ABC, seperate Midis per ABC Track

   void GeneratePreviewMidi2(std::stringstream * abctext, int64_t * buffersize);

   size_t m_Nabctracks;

   std::vector< std::vector<short> > m_WavStreams; // this stores the rendered WAV data for all the ABC Tracks
   std::vector<short> m_StereoStream; // this is the mixed down stream
   std::vector< int > m_WavPannings;

   MidiPreview();  // constructor

   //start time, end time, channel, pitch, velocity, identifier

   std::vector< std::list< ToneTuple > > m_ABCTones;
   std::vector< std::vector< ToneTuple > > m_ABCTonesvector;

   std::vector< std::vector<uint32_t> > m_ToneCounts;  // to measure occupancy in 50ms blocks
   std::vector< uint32_t> m_TotalToneCounts;

   int m_volume = 100;
   int m_panning = 100;

   void CombineTones();

   bool AudioReady = false;
   bool AudioRedrawn = false;

};

// Constructor
MidiPreview::MidiPreview()
{
}

void MidiPreview::GeneratePreviewMidi2(std::stringstream * abctext, int64_t * buffersize)
{
   std::string ABCString = abctext->str();
   m_Nabctracks = Frequency_Substr(ABCString, "X:");
   // std::cout << "The ABC has " <<  m_Nabctracks << " Tracks." << std::endl;

   // Allocate Space for Toneinformation
   m_ABCTones.resize(m_Nabctracks);

   // Allocate Internal Instrument Number List
   std::vector<size_t> myinstrumentnumber;
   myinstrumentnumber.resize(m_Nabctracks);

   // Cut down the text into the ABC parts
   std::vector<std::string> ABCTracks = ABCTextArray(ABCString, 'X');

   // #pragma omp parallel for   // might as well do this in parallel
   uint64_t finalsample=0;
   for (size_t track=1; track < m_Nabctracks+1; track++)
   {
       // empty the tonestart/toneend lists
       int ztrack = track -1 ;
       m_ABCTones[ztrack] = {};
       // make a string stream copy of the track
       std::stringstream mytrack;
       mytrack << ABCTracks[track];     // why do we need to copy all the lines once more into a list? we already got all the text accessible by line

       // and break it down into a list of lines
       std::list< std::string > mytracklines;
       std::string line;
       while ( std::getline(mytrack, line) )
       {
           mytracklines.push_back(line);
       }
       auto lineiterator = mytracklines.begin();
       ++lineiterator; // first line is bogus

       line = *lineiterator; // Instrument from T line

       myinstrumentnumber[ztrack] = GetABCInstrumentFromTLine(line);

       // Panning Info from Z line
       ++lineiterator;
       line = *lineiterator;

       ++lineiterator; ++ lineiterator; ++lineiterator;

       double currenttime = 0.;
       int currentvelocity = 127;

       // this claviature holds tone starting times in samples ( currenttime *0.5 * 44100 )
       std::vector<int64_t> clavi;
       clavi.resize(38);
       std::fill(clavi.begin(), clavi.end(), -1);

       // this claviature holds tone starting velocities
       std::vector<float> clavivel;
       clavivel.resize(38);
       std::fill(clavivel.begin(), clavivel.end(), 0.);

       while ( lineiterator != mytracklines.end() )
       {
           std::string myline = *lineiterator;
           double myduration = 0.;     // so far this line has a 0 duration
           std::list<int> pitchends = {};

           // is this a velocity change?
           if (IsVelchange( myline )) currentvelocity = Velocity( myline );

           // is this a break?
           if (IsBreak(myline)) myduration = BreakDuration(myline);


           if (IsTone(myline))
           {
               myduration = ChordDuration(myline);
               std::deque<int> pitches = GetPitches(myline);

               while (pitches.size() > 0)
               {
                   int mypitch = pitches.front();
                   pitches.pop_front();
                   int cont = pitches.front();
                   pitches.pop_front();

                   // Check if this generated a new tone and if it did .. memorize the time and velocity
                   if ( !(clavi[mypitch] > -1) )
                   {
                       clavi[mypitch] = int64_t(  currenttime*0.5*44100   );
                       clavivel[mypitch] = currentvelocity/128.0;
                   }
                   if (cont == -1)
                   {
                       // the tone end will happen only after the duration .. so we need to memorize this for now
                      // int64_t myqduration = (int64_t( (myduration * 0.5 * 44100) )/100 + 0.5) * 100;  // we are rounding the duration to a length of 100/44100 = 0.0022s = 2.2milliseconds for simplicity
                       int64_t myqduration = (currenttime * 22050 - clavi[mypitch]) + myduration*22050;
                       myqduration = (int64_t(myqduration/100 + 0.5))*100;
                       m_ABCTones[ztrack].push_back( std::make_tuple(
                              myqduration+mypitch,
                              clavi[mypitch],
                              myqduration,
                              0,
                              mypitch+36,
                              clavivel[mypitch]
                                     ));

                                     // we will add the unique identifier here to make it possible to sort by the identifier and avoid multiple renderings
                       if ( finalsample < static_cast<uint64_t>(  clavi[mypitch] + myqduration ))
                                   finalsample = clavi[mypitch] + myqduration;
                       clavi[mypitch] = -1;
                       clavivel[mypitch] = 0.;
                   }
               }
           }
           currenttime = currenttime + myduration;
           ++lineiterator; // take the next line
       }
   }
   uint64_t durationseconds = finalsample / 44100;
   std::cout << "ABC Duration: " << durationseconds << " seconds " << "  or: "<< durationseconds/60 << " minutes and " << durationseconds - (durationseconds/60)*60 << " seconds ." << std::endl;


   // now we know how much space we need for the WAV + 1 second of extra silence - this is stereo, so this is 2 times the size
   //m_StereoStream.resize(finalsample*2 + 88200*2);
   //std::fill(m_StereoStream.begin(), m_StereoStream.end(), short(0));  // wipe the audio preview

   // Tone Count Statistics
   //                duration in seconds       in 50ms blocks
   int64_t chunks = ((finalsample/44100)+2) * 1000 / 50;
   m_ToneCounts.resize( m_Nabctracks );
   for (size_t i = 0; i < m_Nabctracks; i++)
   {
       m_ToneCounts[i].resize(chunks);
       std::fill(m_ToneCounts[i].begin(), m_ToneCounts[i].end(), 0);
   }


   // Turn the list into a vector and sort it
   m_ABCTonesvector.resize(m_Nabctracks);
   for (size_t i = 0; i < m_Nabctracks; i++)
   {
       m_ABCTonesvector[i] = {std::begin(m_ABCTones[i]), std::end(m_ABCTones[i])};
       std::sort( m_ABCTonesvector[i].begin(), m_ABCTonesvector[i].end() );
   }

   //
   //std::vector<short> AudioBuffer={};
  // int64_t silence = 2*44100; // for now we add two seconds of silence after the release


   for (size_t i = 0; i < m_Nabctracks; i++)
   {
    //  std::cout << "Estimating Track " << i << std::endl;
    //  int64_t oldID = -1;
      for (size_t j= 0; j < m_ABCTonesvector[i].size(); j++)
      {

          int64_t tonestart = std::get<1>(m_ABCTonesvector[i][j]);
          int64_t toneduration = std::get<2>(m_ABCTonesvector[i][j]);

          int64_t chunkstart = ( (tonestart * 1000) / (44100*50) );
          int64_t chunkduration = ( toneduration * 1000 ) / (44100*50);

          int instrunumber = myinstrumentnumber[i];

          if (  fadeouttype[ instrunumber ] == 0 )
          {
              // this is a constant duration instrument
              size_t loopend = chunkstart + fadeout[instrunumber];
              if (loopend >= m_ToneCounts[i].size()) loopend = m_ToneCounts[i].size() ;

              for (size_t m = chunkstart; m < loopend; m++) m_ToneCounts[i][m] += 1;

          }
          else
          {
              size_t loopend = chunkstart + chunkduration + fadeout[instrunumber];
              if (loopend >= m_ToneCounts[i].size()) loopend = m_ToneCounts[i].size() ;
              // this is a continuous instrument
              for (size_t m = chunkstart; m < loopend; m++) m_ToneCounts[i][m] += 1;
        }
      }
   }

   m_TotalToneCounts.resize(691);
   std::fill(m_TotalToneCounts.begin(), m_TotalToneCounts.end(), 0);
   float chunksperpixel =  690.0 / m_ToneCounts[0].size();

   for ( uint64_t i = 0; i < m_ToneCounts[0].size(); i++ )
   {
        // count full number of tones per slot and pick largest
      uint32_t val = 0;
      for (size_t j = 0; j < m_ToneCounts.size(); j++) // loop over tracks
      {
         val = val + m_ToneCounts[j][i];
      }
      if (val > 99) val = 99;
      size_t position = size_t(i * chunksperpixel);
      if ( val > m_TotalToneCounts[position] ) m_TotalToneCounts[position] = val;
   }

   AudioReady = true;
   AudioRedrawn = false;
}




#endif
