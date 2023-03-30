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

   std::vector< std::list< ToneTuple > > m_ABCTones = {};
   std::vector< std::vector< ToneTuple > > m_ABCTonesvector = {}; //
   std::vector<size_t> m_instrumentnumber = {};     // Instrument of the ABC tracks
   std::vector<size_t> m_Xnumber = {};

   std::size_t Nabctracks();

private:

   std::size_t m_Nabctracks = 0;

   std::vector< ABCHeaderT > m_abcheaders;

};


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
   m_ABCTones.resize(m_Nabctracks);

   // Cut down the text into the ABC parts
   std::vector<std::string> ABCTracks = ABCTextArray(ABCString, "X:");

   // ABCTracks[0] is the header of the ABC, usually containing information about the ABC transcoding program that was used, doesn't matter to us
   for (size_t abctrack = 0; abctrack < m_Nabctracks; abctrack++)
   {
       // Now we are in the first ABC Track

       // we break it down into a list of lines
       std::stringstream alllines;
       alllines << ABCTracks[abctrack+1];
       std::list< std::string > mytracklines;
       std::list< std::string > mytrackheader;

       ABCSplitHeaderBody(alllines, mytracklines, mytrackheader);

       // Assign header info to this abctrack header
       for (auto line : mytrackheader) m_abcheaders[abctrack].ParseLine(line);

       // Understand Header
            // X: for part number, T: line for instrument, Z: for Stereo Position, Q for speed, L for unit note length


       // Understand Body

       // We start with 0 tones
       m_ABCTones[abctrack].resize(0);
   }
}

void ABCInput::LoadABC(std::string filename)
{

}


#endif
