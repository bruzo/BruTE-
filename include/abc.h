#ifndef ABC_H
#define ABC_H

// Class to handle everything about the input of ABC Files: loading / parsing and turning it into playable information for the audioplayer

#include<vector>
#include<list>
#include<string>

#include "brutedefinitions.h"
#include "abcheadert.h"



typedef std::tuple< int64_t, int64_t, int64_t, int, int, float > ToneTuple;





class ABCInput
{
public:

   void LoadABC(std::stringstream * abctext);
   void LoadABC(std::string filename);

   std::vector< std::vector< ToneTuple > > m_ABCTonesvector = {};

   std::vector< std::vector<uint32_t> > m_ToneCounts;  // to measure occupancy in 50ms blocks
   std::vector< uint32_t> m_TotalToneCounts;
   std::string  CorrectForMaestro(std::string abctext);



   std::size_t Nabctracks();

   int64_t GetDuration();

   int GetStereoPosition(int abctrack);
   void SetStereoPosition(int abctrack, int value);

   int GetDepthPosition(int abctrack);
   void SetDepthPosition(int abctrack, int value);

   int GetID(int abctrack);
   void SetID(int abctrack, int value);

   int GetX(int abctrack);
   void SetX(int abctrack, int value);

   int GetInstrument(int abctrack);
   void SetInstrument(int abctrack, int value);

   void UpdateToneCounts();
   bool AudioReady = false;
   bool AudioRedrawn = false;

private:

   std::size_t m_Nabctracks = 0;

   std::vector< ABCHeaderT > m_abcheaders;

   int64_t m_durationseconds = 0;

};

void ABCInput::UpdateToneCounts()
{
   int64_t chunks = ((m_durationseconds+2) * 1000) / 50;

   m_ToneCounts.resize( m_Nabctracks );
   for (size_t i = 0; i < m_Nabctracks; i++) m_ToneCounts[i].resize(chunks, 0);

   for (size_t i = 0; i < m_Nabctracks; i++)
   {
      for (size_t j= 0; j < m_ABCTonesvector[i].size(); j++)
      {
          int64_t tonestart = std::get<1>(m_ABCTonesvector[i][j]);
          int64_t toneduration = std::get<2>(m_ABCTonesvector[i][j]);

          int64_t chunkstart = ( (tonestart * 1000) / (44100*50) );
          int64_t chunkduration = ( toneduration * 1000 ) / (44100*50);

          int instrunumber = GetInstrument(i);

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

int ABCInput::GetInstrument(int abctrack)
{
    return m_abcheaders[abctrack].GetInstrument();
}

void ABCInput::SetInstrument(int abctrack, int value)
{
    m_abcheaders[abctrack].SetInstrument(value);
}

void ABCInput::SetX(int abctrack, int value)
{
    m_abcheaders[abctrack].SetX(value);
}

int ABCInput::GetX(int abctrack)
{
    return m_abcheaders[abctrack].GetX();
}

int ABCInput::GetID(int abctrack)
{
    return m_abcheaders[abctrack].GetID();
}

void ABCInput::SetID(int abctrack, int value)
{
    m_abcheaders[abctrack].SetID(value);
}


int ABCInput::GetDepthPosition(int abctrack)
{
    return m_abcheaders[abctrack].GetDepthPosition();
}

void ABCInput::SetDepthPosition(int abctrack, int value)
{
    m_abcheaders[abctrack].SetDepthPosition(value);
}


int ABCInput::GetStereoPosition(int abctrack)
{
    return m_abcheaders[abctrack].GetStereoPosition();
}

void ABCInput::SetStereoPosition(int abctrack, int value)
{
    m_abcheaders[abctrack].SetStereoPosition(value);
}

int64_t ABCInput::GetDuration()
{
    return m_durationseconds;
}

std::size_t ABCInput::Nabctracks()
{
    return m_Nabctracks;
}

std::string ABCInput::CorrectForMaestro(std::string abctext)
{
   std::stringstream inabc(abctext);
   std::stringstream outabc("");
   std::string line;
   while (std::getline( inabc , line))
   {
       if ( line.find("|") != std::string::npos )
       {
          // ok we have a abc line with tone information
         // std::vector<char> pitchchangedup = {};
         // std::vector<char> pitchchangeddown = {};
          std::vector<int> tones(line.size());

          for (size_t i = 0; i < line.size()-1; i++)
          {
              tones[i] = LetterIndex(line[i]);
          }

          for (size_t i = 0; i < line.size()-1; i++)
          {
              if ((line[i]=='^') && (tones[i+1]>-1))
              {
                  for (size_t j = i+2; j < line.size()-1; j++)
                  {
                      if ((tones[j] == tones[i+1]) && (line[j-1]!='^'))
                      {
                          line.insert(j, "^");
                          tones.insert(tones.begin() + j, -1);
                      }
                  }
              }
          }
      //    std::cout << line << std::endl;
          outabc << line << std::endl;
       }
       else
       {
       outabc << line << std::endl;
       }
   }
   return outabc.str();
}

// Parse an ABC from a Stringstream
void ABCInput::LoadABC(std::stringstream * abctext)
{
   // cast input stream into a std::string
   std::string ABCString = abctext->str();

   // Check if this ABC was made with BrutE
   bool Maestro = false;
   bool Firefern = false;
   if ( ABCString.find("Bruzo") == std::string::npos )
   {
       if (ABCString.find("Maestro")!= std::string::npos ) Maestro = true;

       if (ABCString.find("Firefern")!=std::string::npos ) Firefern = true;
   }

   if (Maestro)
   {
       std::cout << " Was made with Maestro " << std::endl;
       ABCString = CorrectForMaestro(ABCString);
   }

   if (Firefern)
   {
       std::cout << " Was made with Firefern " << std::endl;
   }

   this->m_Nabctracks = Frequency_Substr(ABCString, "X:");
 //  std::cout << "ABC IMPORT The ABC has " <<  this->m_Nabctracks << " Tracks." << std::endl;

   // ABC Track information arrays
   m_abcheaders.resize(m_Nabctracks);

   // ABC Track tone info
   m_ABCTonesvector.resize(m_Nabctracks);

   // Cut the full text into the ABC parts starting with X:
   std::vector<std::string> ABCTracks = ABCTextArray(ABCString, "X:");

   uint64_t finalsample = 0;

   // ABCTracks[0] is the header of the ABC, usually containing information about the ABC transcoding program that was used, doesn't matter to us
   for (size_t abctrack = 0; abctrack < m_Nabctracks; abctrack++)
   {


       // We start with 0 tones in this track of course
       m_ABCTonesvector[abctrack].resize(0);
   //    m_ABCTonesvector[abctrack].clear();
     //  m_ABCTonesvector[abctrack].reserve(1000);

       // we break it down into a list of lines
       std::stringstream alllines;
       alllines << ABCTracks[abctrack+1];

       std::vector< std::string > mytracklines;
       std::vector< std::string > mytrackheader;
       ABCSplitHeaderBody(alllines, mytracklines, mytrackheader);

      // std::cout << "ABC cut down " << std::endl;

       // Assign header info to this abctrack header
       for (auto line : mytrackheader) m_abcheaders[abctrack].ParseLine(line);

       int16_t myinstrument = m_abcheaders[abctrack].GetInstrument();

       double beat_to_seconds = m_abcheaders[abctrack].GetBeatsToSeconds();
       //std::cout << "Beats to Seconds" << beat_to_seconds << " Should be 0.48 " << std::endl;
       // Preparations to play the song and figure out tone starting/ending times

       double currenttime = 0.;
       int currentvelocity = 0; // corresponds to +pppp+

       // this claviature holds tone starting times in samples @44.1KHz ( currenttime *0.5 * 44100 )
       std::vector<int64_t> clavi;
       clavi.resize(38); for (size_t i= 0; i < clavi.size(); i++) clavi[i] = -1;

        // this claviature holds tone starting velocities
       std::vector<int64_t> clavivel;
       clavivel.resize(38); for (size_t i=0; i < clavivel.size(); i++) clavivel[i]=0;

       // Now go through this abc track
       for (auto line : mytracklines)
       {
          // std::cout << line << std::endl;

           double myduration = 0.;        // so far this line has a 0 duration
           std::vector<int16_t> pitchends = {}; // and so far this line has no ending pitches

           // is this a velocity change?
           if (IsVelchange( line )) {
                 currentvelocity = Velocity( line );
           } else
           {

              // is this a break?
              if (IsBreak(line))
              {
                  myduration = BreakDuration(line) * beat_to_seconds;
              }else
              {
              // if it is not a break and not a tempo change and we eliminated everything .. this should be a tone

                //  std::cout << line << std::endl;
                  myduration = ChordDuration(line) * beat_to_seconds ;
               //   std::cout << "Duration " << myduration << "  beatstosecs" << beat_to_seconds  <<  std::endl;
                  std::vector<int16_t> pitches = GetPitches2(line);
             //     std::cout << "Pitches ";
               //   for (size_t i = 0; i < pitches.size(); i++) std::cout << pitches[i] <<  "  ";
               //   std::cout << std::endl;


                  while (pitches.size() > 0)   // process them after each other
                  {   // get pitch and continuation info for each pitch fired in this chord/tone
                      int16_t cont = pitches.back(); pitches.pop_back();
                      int16_t mypitch = pitches.back(); pitches.pop_back();

                     // std::cout << mypitch << "  " << cont << std::endl;
                      // if this tone doesn't run, we switch it on
                      if ( !(clavi[mypitch] > -1) )
                      {
                          clavi[mypitch] = int64_t(  currenttime * 44100   );
                          clavivel[mypitch] = currentvelocity;
                      }

                      if (cont == -1)
                      {
                          // this tone end will happen after this duration
                         // std::cout << "mypitch  "  << mypitch << std::endl;
                          int64_t myqduration = ( currenttime * 44100 - clavi[mypitch] ) + myduration * 44100;


                          m_ABCTonesvector[abctrack].emplace_back(
                               std::make_tuple(
                                 clavi[mypitch], clavi[mypitch],  // starting time 2 times (redundant to be removed )
                                 myqduration,  // ending time
                                 myinstrument, // instrument number
                                 mypitch+36,       // pitch
                                 clavivel[mypitch] // velocity
                                 ));

                          if ( finalsample < static_cast<uint64_t>(clavi[mypitch] + myqduration) )
                                   finalsample = clavi[mypitch] + myqduration;
                          clavi[mypitch] = -1;
                          clavivel[mypitch] = 0.;
                      }
                  }
              }
          }
          currenttime = currenttime + myduration;
       }
   }

   m_durationseconds = finalsample / 44100;
   // Turn the list into a vector and sort it by the tone starting times - not sure if that is necessary, but who knows
   for (size_t i = 0; i < m_Nabctracks; i++)
   {
       std::sort( m_ABCTonesvector[i].begin(), m_ABCTonesvector[i].end() );
   }
   std::cout << "ABC Tones read in " << std::endl;
}

void ABCInput::LoadABC(std::string filename)
{

}


#endif
