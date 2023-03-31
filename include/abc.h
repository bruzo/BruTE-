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

   std::vector<size_t> m_instrumentnumber = {};     // Instrument of the ABC tracks
   std::vector<size_t> m_Xnumber = {};

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

private:

   std::size_t m_Nabctracks = 0;

   std::vector< ABCHeaderT > m_abcheaders;

   int64_t m_durationseconds = 0;

};

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



// Parse an ABC from a Stringstream
void ABCInput::LoadABC(std::stringstream * abctext)
{
   // cast input stream into a std::string
   std::string ABCString = abctext->str();

   this->m_Nabctracks = Frequency_Substr(ABCString, "X:");
   std::cout << "ABC IMPORT The ABC has " <<  this->m_Nabctracks << " Tracks." << std::endl;

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

       // we break it down into a list of lines
       std::stringstream alllines;
       alllines << ABCTracks[abctrack+1];

       std::vector< std::string > mytracklines;
       std::vector< std::string > mytrackheader;
       ABCSplitHeaderBody(alllines, mytracklines, mytrackheader);

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
       clavi.resize(38, -1);

        // this claviature holds tone starting velocities
       std::vector<int16_t> clavivel;
       clavivel.resize(38, 0);

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

                 // std::cout << line << std::endl;
                  myduration = ChordDuration(line) * beat_to_seconds ;

                  std::vector<int16_t> pitches = GetPitches2(line);


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


                          m_ABCTonesvector[abctrack].push_back(
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

}

void ABCInput::LoadABC(std::string filename)
{

}


#endif
