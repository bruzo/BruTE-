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

   void GeneratePreviewMidi(std::stringstream * abctext, int64_t buffersize);
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



private:

   // Functions to make the conversion
   int Velocity(std::string input);
   int WhichInstrument(std::string input);
   int WhichInstrumentNumber(std::string input);
   bool IsVelchange(std::string input);
   bool IsBreak(std::string input);
   bool IsTone(std::string input);
   double BreakDuration(std::string input);
   double ChordDuration(std::string input);
   double EvaluateDurationString(std::string input);
   std::deque<int> GetPitches(std::string input);

   // Helper Functions to Cut down the Text
   size_t Frequency_Substr(std::string strfull,std::string substring);
   std::vector<std::string> ABCTextArray( std::string input );

    // tsf* TinySoundFont;

};

// Constructor
MidiPreview::MidiPreview()
{
   // load the soundfont
   // std::cout << "Loading Soundfont" << std::endl;
   // TinySoundFont = tsf_load_filename("sfnew.sf2");
   // std::cout << "Soundfont loaded" << std::endl;
   //TinySoundFont = tsf_load_memory(MinimalSoundFont, sizeof(MinimalSoundFont));

   // set the render engine to 44kHz, Mono
   // tsf_set_output(TinySoundFont, TSF_MONO, 44100, 0); //sample rate

   /*
   tsf_note_on(TinySoundFont, 0, 60, 1.0f); //preset 0, middle C
   short HalfSecond[22050]; //synthesize 0.5 seconds
   tsf_render_short(TinySoundFont, HalfSecond, 22050, 0);
   */
}

void MidiPreview::GeneratePreviewMidi(std::stringstream * abctext, int64_t buffersize)
{
   std::string ABCString = abctext->str();
   m_Nabctracks = Frequency_Substr(ABCString, "X:");

   std::cout << "The ABC has " <<  m_Nabctracks << " Tracks." << std::endl;
   //std::cout << "Last Event is at " << lasttone << std::endl;

   // Make sure we have the empty MidiFile instances
   // PreviewMidiTracks.resize(m_Nabctracks);
   // for (size_t i = 0; i<PreviewMidiTracks.size(); i++) PreviewMidiTracks[i] = smf::MidiFile();

   // Make sure we have enough WAV Streams
   // m_WavStreams.resize(m_Nabctracks);
   // Now set them to a proper length and delete everthing that was inside
   /*
   for (size_t i = 0; i < m_WavStreams.size(); i++)
   {
       m_WavStreams[i].resize(buffersize*2);
       std::fill(m_WavStreams[i].begin(), m_WavStreams[i].end(), short(0));
   }
*/
   m_StereoStream.resize(buffersize*4.1);
   std::fill(m_StereoStream.begin(), m_StereoStream.end(), short(0));


   m_WavPannings.resize(m_Nabctracks);
   for (size_t i = 0; i < m_WavPannings.size(); i++)
       m_WavPannings[i]=64;

   short myBuffer[ 44100*3 ]; //synthesize buffer for 3 seconds


   std::vector<std::string> ABCTracks = ABCTextArray(ABCString); // Cut down the text into ABC parts



 //  std::cout << "We found " << ABCTracks.size() << " ABC Tracks in the Mapping " << std::endl;

   // Now we got all the ABC Tracks separated, ABCTextArray[0] is just the header so 1 to N+1 are the tracks

   // might as well do this in parallel
   // #pragma omp parallel for
   for (size_t track=1; track < m_Nabctracks+1; track++)
   {
       // empty the tonestart/toneend lists
       int ztrack = track -1 ;

       // make a string stream copy of the track
       std::stringstream mytrack;
       mytrack << ABCTracks[track];

       // why do we need to copy all the lines once more into a list? we already got all the text accessible by line

       // and break it down into a list of lines
       std::list< std::string > mytracklines;
       std::string line;
       while ( std::getline(mytrack, line) )
       {
           mytracklines.push_back(line);
       }
       auto lineiterator = mytracklines.begin();
    //   std::cout << "We found " << mytracklines.size() << " Lines in the ABC " << std::endl;
       ++lineiterator; // first line is bogus

       // Instrument from T line
       line = *lineiterator; // this is the line with the instrument

       std::string myinstrument = line.substr(line.find_last_of("[")+1,line.find_last_of("]") ); // we only use instruments defined between [] in the T line
       myinstrument.pop_back();

       // Panning Info from Z line
       ++lineiterator;
       line = *lineiterator;
       auto ps = split(line, ' ');
       int panning = std::stoi( ps[ ps.size()-1 ] );

       m_WavPannings[ztrack] = panning;  // keep this for later

       // the next three line we ignore, as all the BruTE ABCs have identical timings
       ++lineiterator; ++ lineiterator; ++lineiterator;

       // Parse Instrument String to ChannelNumber
       int MidiChannel = WhichInstrument(myinstrument);
      // int TinyMidiChannel = tsf_get_presetindex( TinySoundFont , 0, MidiChannel);

       std::cout << "Track: " << track << " \t " << myinstrument << "\t MidiChannel "<< MidiChannel  << " \t  Panning " << panning << std::endl;

    //   PreviewMidiTracks[mytracknumber].addTempo(0, 0, 125);
    //   PreviewMidiTracks[mytracknumber].addTracks(1);
    //   PreviewMidiTracks[mytracknumber].addTimbre(0, 0, 0, MidiChannel);
       // int tpq     = PreviewMidiTracks[mytracknumber].getTPQ();

       // now the fun starts generating tones from the chords
       double currenttime = 0.;
    //   int currentvelocity = 127;

       // to keep track of registers on and off
       std::vector<bool> claviature;
       claviature.resize(38);
       std::fill(claviature.begin(), claviature.end(), false);

       while ( lineiterator != mytracklines.end() )
       {
           std::string myline = *lineiterator;
           //std::cout << myline << std::endl;
           double myduration = 0.;     // so far this line has a 0 duration
           std::list<int> pitchends = {};

           // is this a velocity change?
           if (IsVelchange( myline ))
           {
              //  currentvelocity = Velocity( myline );
           }

           // is this a break?
           if (IsBreak(myline))
           {
               myduration = BreakDuration(myline);
           }

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

                   // Check if this generated a new tone start event
                   if ( !claviature[mypitch] )
                   {
                       claviature[mypitch] = true;
                       // int thistick = int( currenttime *tpq  );
                       // PreviewMidiTracks[mytracknumber].addNoteOn(1, thistick,0, mypitch+36, currentvelocity);

                       // also switch on tone in tinysf
                 //      tsf_note_on(TinySoundFont, TinyMidiChannel, mypitch+36, currentvelocity/128.0 ); //preset 0, middle C , MidiChannel!
                   }
                   if (cont == -1)
                   {
                       // this tone ends here
                       claviature[mypitch] = false;

                      //  int thistick = int( (currenttime+myduration)*tpq  );
                      // PreviewMidiTracks[mytracknumber].addNoteOff(1, thistick,0, mypitch+36); //

                       // the tone end will happen only after the duration .. so we need to memorize this for now
                       pitchends.push_front(mypitch+36);
                   }
               }
           }
           // Render a bit into the WAV stream

           // calculations for timings:
           //     currenttime/ 2 = current time in seconds
           //     (currenttime / 2) * 44100 in samples


           int64_t currentsampleposition = int64_t(currenttime*0.5 * 44100);
           int64_t currentbuffer = int64_t(myduration * 0.5 * 44100);

           // we only render if this had a duration
           if ( currentbuffer > 0)
           {


          //    tsf_render_short(TinySoundFont, myBuffer, int(currentbuffer), 0);  // render this duration

              for (int64_t cp = 0; cp < currentbuffer; cp++){
                 // m_WavStreams[mytracknumber][currentsampleposition + cp] = myBuffer[cp];

                 int mypanning = (( panning - 64 ) *  m_panning)/100 + 64;

                 float weightleft = ((mypanning) / 128.0);
                 float weightright = ((1.0 - weightleft));

                 weightleft = (weightleft * m_volume)/100.0;
                 weightright = (weightright * m_volume)/100.0;

                 m_StereoStream[2*cp   +currentsampleposition*2] += int( myBuffer[cp] * weightleft);            // left channel
                 m_StereoStream[2*cp+1 +currentsampleposition*2] += int( myBuffer[cp] * weightright);

              }
           }

           currenttime = currenttime + myduration;

           // now take the tone end events and write them into tsf and our data structure
           for (std::list<int>::iterator ip=pitchends.begin(); ip!=pitchends.end(); ip++)
           {
        //        tsf_note_off(TinySoundFont, TinyMidiChannel, *ip);  // Midichannel
           }


           ++lineiterator; // take the next line
       }
   }

/*
   std::cout << " Writing WAV Track " << std::endl;

   STEREO_WAV_HEADER myheader;
   myheader.Subchunk2Size = uint32_t(m_StereoStream.size());

   std::stringstream myfilename;
   FILE * myfile;
   myfile = fopen("audio.wav", "wb");
   fwrite(&myheader, 1, sizeof(STEREO_WAV_HEADER), myfile );
   fwrite( m_StereoStream.data() , 1, m_StereoStream.size()*sizeof(short), myfile);
   fclose(myfile);
*/
}

bool ToneCompare (const ToneTuple &lhs, const ToneTuple &rhs){
  return std::get<0>(lhs) < std::get<0>(rhs);
}

void MidiPreview::GeneratePreviewMidi2(std::stringstream * abctext, int64_t * buffersize)
{
   std::string ABCString = abctext->str();
   m_Nabctracks = Frequency_Substr(ABCString, "X:");
   std::cout << "The ABC has " <<  m_Nabctracks << " Tracks." << std::endl;

   // Allocate Panning Information
   m_WavPannings.resize(m_Nabctracks);
   for (size_t i = 0; i < m_WavPannings.size(); i++)
       m_WavPannings[i]=64;

   // Allocate Space for Toneinformation
   m_ABCTones.resize(m_Nabctracks);

   // Allocate Internal Instrument Number List
   std::vector<size_t> myinstrumentnumber;
   myinstrumentnumber.resize(m_Nabctracks);

   // Cut down the text into the ABC parts
   std::vector<std::string> ABCTracks = ABCTextArray(ABCString);

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

       // we only use instruments defined between [] in the T line
       std::string myinstrument = line.substr(line.find_last_of("[")+1,line.find_last_of("]") );
       myinstrument.pop_back();

       // Panning Info from Z line
       ++lineiterator;
       line = *lineiterator;
       auto ps = split(line, ' ');
       int panning = std::stoi( ps[ ps.size()-1 ] );
       m_WavPannings[ztrack] = panning;  // keep this for later

       // the next three line we ignore, as all the BruTE ABCs have identical timings and we do not make music with foreign ABC flavors yet
       ++lineiterator; ++ lineiterator; ++lineiterator;

       // Parse Instrument String to ChannelNumber
     //  int MidiChannel = WhichInstrument(myinstrument);
       //int TinyMidiChannel = tsf_get_presetindex( TinySoundFont , 0, MidiChannel);
       myinstrumentnumber[ztrack] = WhichInstrumentNumber(myinstrument);

       std::cout << "Track: " << track << " \t " << myinstrument << " \t  Panning " << panning << std::endl;

       // now the fun starts generating tones from the chords
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
      std::cout << "Estimating Track " << i << std::endl;
      int64_t oldID = -1;
      for (size_t j= 0; j < m_ABCTonesvector[i].size(); j++)
      {
          int64_t newID = std::get<0>(m_ABCTonesvector[i][j]);

          int64_t tonestart = std::get<1>(m_ABCTonesvector[i][j]);
          int64_t toneduration = std::get<2>(m_ABCTonesvector[i][j]);
      //    int64_t samplelength = toneduration + silence;
          float tonevelocity = std::get<5>(m_ABCTonesvector[i][j]);

          if ( newID != oldID) // this is a new tone so we have to render it
          {
         //     int midichannel = std::get<3>(m_ABCTonesvector[i][j]);
          //    int tonepitch = std::get<4>(m_ABCTonesvector[i][j]);

             // if (AudioBuffer.size() < samplelength ) AudioBuffer.resize(samplelength);

             // std::fill(AudioBuffer.begin(), AudioBuffer.end(), 0);  // wipe the audiobuffer to be certain, always better with STL than own loop :)

             // tsf_reset(TinySoundFont);  // reset our synthesizer

              // turn on the tone, render the duration, then turn of the tone, render the release sound
             // tsf_note_on(TinySoundFont, midichannel, tonepitch, 105.0/128.0 );
             // tsf_render_short(TinySoundFont, &AudioBuffer[0], toneduration, 0);
             // tsf_note_off(TinySoundFont, midichannel, tonepitch);
             // tsf_render_short(TinySoundFont, &AudioBuffer[toneduration], silence, 0);
          }

          // now copy the sample into the right position of the stream
          int mypanning = (( m_WavPannings[i] - 64 ) *  m_panning)/100 + 64;
          float velfactor = 1.895 * tonevelocity - 0.555; // empiric formula that captures the difference in amplitude as a function of velocity, based on measurements in the game

          float weightleft = ((mypanning) / 128.0)*velfactor;   // panning
          float weightright = ((1.0 - weightleft))*velfactor;

          weightleft = (weightleft * m_volume)/100.0;   // volume rescale
          weightright = (weightright * m_volume)/100.0;
/*
          for (int64_t cp = 0; cp < samplelength; cp++)
          {
             m_StereoStream[ 2*cp + tonestart*2  ] += short( AudioBuffer[cp] * weightleft);
             m_StereoStream[2*cp + tonestart*2 +1] += short( AudioBuffer[cp] * weightright);
          }
          */
     //     oldID = newID;

          // now we gotta count tones for the tonecounting preview

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
         // std::cout << std::get<0>(m_ABCTonesvector[i][j]) << "  " << std::get<1>(m_ABCTonesvector[i][j]) << std::endl;1

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
   // to check: difference in volume between the velocities:  ppp : 51, pp 64, p 73, mp 82, mf 89, f 96, ff 102, fff105
   // for that we'll do same tone at 105 always and need "amplification factor for  fff-to-ff, etcc
}



std::vector<std::string> MidiPreview::ABCTextArray( std::string input)
{
    std::stringstream abctext;
    abctext << input;

    std::vector<std::string> returntext;


    std::string line;
    std::stringstream abcblock;

    std::getline(abctext, line);
    while ( !abctext.eof() )
    {
        if (line[0] == 'X')
        {
            returntext.push_back(abcblock.str());
            abcblock.str(std::string());
        }

        abcblock << line << std::endl;
        std::getline(abctext, line);
    }
    returntext.push_back(abcblock.str());

    return returntext;
}


size_t MidiPreview::Frequency_Substr(std::string strfull,std::string substring)
{
    int counter=0;
    for (size_t i = 0; i <strfull.size()-1; i++)
    {
        size_t m = 0;
        size_t n = i;
        for (size_t j = 0; j < substring.size(); j++)
        {
            if (strfull[n] == substring[j])
            {
                m++;
            }
            n++;
        }
        if (m == substring.size())
        {
            counter++;
        }
    }
    return counter;
}


int MidiPreview::Velocity(std::string input)
{
    for (auto it = MidiVelocities.begin(); it != MidiVelocities.end(); ++it)
          if ( input.compare(it->first) == 0 )
             return it->second;
    return 0;
}

// resolve the name of the instrument into the midi channel
int MidiPreview::WhichInstrument(std::string input)
{
    for (auto it = InstrumentMidiChannels.begin(); it != InstrumentMidiChannels.end(); ++it)
          if ( input.compare(it->first) == 0 )
             return it->second;
    return 0;
}

// resolve the name of the instrument into the internal instrument number
int MidiPreview::WhichInstrumentNumber(std::string input)
{
    for (auto it = InstrumentMidiNumbers.begin(); it != InstrumentMidiNumbers.end(); ++it)
          if ( input.compare(it->first) == 0 )
             return it->second;
    return 0;
}

bool MidiPreview::IsBreak(std::string input)
{
    if (input.length()>0)  // any break must have at least a "z"
    {
        if (input.at(0) == 'z')
        {
            return true;
        }
        else return false;
    }
    else return false;
}

bool MidiPreview::IsTone(std::string input)
{
    if (input.length()>0)  // any break must have at least a "z"
    {
        if (input.at(0) == '[')
        {
            return true;
        }
        else return false;
    }
    else return false;
}

bool MidiPreview::IsVelchange(std::string input)
{
   if (input.length() > 2) // a velocity change always has at least 3 characters
   {
   if (input.at(0)=='+')
       {
           return true;
       }
       else
       {
           return false;
       }
   }
   else
   {
       return false;
   }
}

double MidiPreview::BreakDuration(std::string input)
{
   std::string onlyduration = input.erase(0,1);
   return EvaluateDurationString(onlyduration);
}

double MidiPreview::ChordDuration(std::string input)
{
    std::string myinput = input;
    std::vector< char > forbidden = { 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'A', 'a', 'B', 'b', '^', '_', '[', ']', '=', ',', '-', ("'")[0] };
    // first Replace all Characters with spaces
    for (size_t i = 0; i < myinput.length(); i++)
    {
        for (size_t j = 0; j < forbidden.size(); j++)
        if ( myinput.at(i)== forbidden.at(j))
        {
            myinput[i] = ' ';
        }
    }
    std::string myduration = split(myinput, ' ')[0];

    return EvaluateDurationString(myduration);
}

std::deque<int> MidiPreview::GetPitches(std::string input)
{
    std::string myinput = input;
    std::vector< char > forbidden = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/', '[', ']'};
    for (size_t i = 0; i < myinput.length(); i++)
    {
        for (size_t j = 0; j < forbidden.size(); j++)
            if (myinput.at(i)==forbidden.at(j))
               myinput[i] = ' ';
    }

    // now make sure continuation signs are distinguishable
    for (size_t i=0; i < myinput.length(); i++)
    {
        if ( myinput.at(i)=='-' ) myinput.insert(i+1, " ");
    }

    std::vector<std::string> mytokens = split(myinput, ' ');

    // now parse the objects
    std::deque<int> returnvalue;
    int waslastapitch = 0;

    /*
    for (size_t i = 0; i < mytokens.size(); i++)
        std::cout << mytokens[i] << " ";
    std::cout << std::endl;
*/
    for (size_t i =0; i < mytokens.size(); i++)
    {
        if (mytokens[i]=="-")
        { // this was a continuation sign
            returnvalue.push_back(-2);
            waslastapitch = 0; // now the last one wasn't a pitch
        }
        else
        {
            // this wasn't a continuation sign, but last one was a pitch, so this tone ends here and we have to add that information
            if (waslastapitch == 1)
            {
                waslastapitch = 0; // now the last one wasn't a pitch
                returnvalue.push_back(-1);
            }


            {
                // this was actually a pitch, we have to find it's value
                waslastapitch = 1;  // now the last one was a pitch
                // first find if this is transposed one up or down
                int relpitch = 0;
                if (mytokens[i].at(0)=='^') relpitch = 1;
                if (mytokens[i].at(0)=='_') relpitch = -1;
                mytokens[i].erase(0,1);

                // now we definitely have to start with a letter
                if ( mytokens[i].at(0) == 'C' ) relpitch += 12;
                if ( mytokens[i].at(0) == 'D' ) relpitch += 14;
                if ( mytokens[i].at(0) == 'E' ) relpitch += 16;
                if ( mytokens[i].at(0) == 'F' ) relpitch += 17;
                if ( mytokens[i].at(0) == 'G' ) relpitch += 19;
                if ( mytokens[i].at(0) == 'A' ) relpitch += 21;
                if ( mytokens[i].at(0) == 'B' ) relpitch += 23;
                if ( mytokens[i].at(0) == 'c' ) relpitch += 24;
                if ( mytokens[i].at(0) == 'd' ) relpitch += 26;
                if ( mytokens[i].at(0) == 'e' ) relpitch += 28;
                if ( mytokens[i].at(0) == 'f' ) relpitch += 29;
                if ( mytokens[i].at(0) == 'g' ) relpitch += 31;
                if ( mytokens[i].at(0) == 'a' ) relpitch += 33;
                if ( mytokens[i].at(0) == 'b' ) relpitch += 35;
                mytokens[i].erase(0,1);

                // and finally we can only have a "," or a "'" to raise or lower it by an octave
                if ( mytokens[i].length() > 0)
                {
                    if (mytokens[i].at(0) == ',') {relpitch -= 12;}
                    else {relpitch += 12;}
                }
                returnvalue.push_back( relpitch );
            }
        }
    }

    // last one was a pitch, there was no -, so this one is discontinued
    if (waslastapitch == 1)
    {
        returnvalue.push_back(-1);
    }

    /*
    for (size_t i=0; i < returnvalue.size(); i++)
        std::cout << returnvalue[i] << " ";
    std::cout<< std::endl;
*/
    return returnvalue;
}

double MidiPreview::EvaluateDurationString(std::string input)
{
    // if the length is 0 this is easy
    if (input.length() == 0) return 1.0;

    // Now Check if this is a fraction
    if (input.find('/') > 0)   // this is a fraction
    {
        std::vector<std::string> twovalues = split(input, '/');
        return ( 1.0 * std::stoi(twovalues.at(0)) / (1.0 * std::stoi(twovalues.at(1))) );
    }
    else        // this is not a fraction
    {
        std::stoi(input);
    }

    return 0.;
}

#endif
