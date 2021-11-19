#ifndef BRUTEDEFS_H
#define BRUTEDEFS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>



    // General MIDI instrument names:
    std::string GMinstrument[128] = { "acpiano", "britepno", "synpiano", "honkytonk", "epiano1", "epiano2", "hrpschrd", "clavinet", "celeste", "glocken", "musicbox", "vibes", "marimba", "xylophon", "tubebell", "santur", "homeorg", "percorg", "rockorg", "churchorg", "reedorg", "accordn", "harmonica", "concrtna", "nyguitar", "acguitar", "jazzgtr", "cleangtr", "mutegtr", "odguitar", "distgtr", "gtrharm", "acbass", "fngrbass", "pickbass", "fretless", "slapbas1", "slapbas2", "synbass1", "synbass2", "violin", "viola", "cello", "contraba", "marcato", "pizzcato", "harp", "timpani", "marcato", "slowstr", "synstr1", "synstr2", "choir", "doo", "voices", "orchhit", "trumpet", "trombone", "tuba", "mutetrum", "frenchorn", "hitbrass", "synbras1", "synbras2", "sprnosax", "altosax", "tenorsax", "barisax", "oboe", "englhorn", "bassoon", "clarinet", "piccolo", "flute", "recorder", "woodflut", "bottle", "shakazul", "whistle", "ocarina", "sqrwave", "sawwave", "calliope", "chiflead", "charang", "voxlead", "lead5th", "basslead", "fantasia", "warmpad", "polysyn", "ghostie", "bowglass", "metalpad", "halopad", "sweeper", "aurora", "soundtrk", "crystal", "atmosphr", "freshair", "unicorn", "sweeper", "startrak", "sitar", "banjo", "shamisen", "koto", "kalimba", "bagpipes", "fiddle", "shannai", "carillon", "agogo", "steeldrum", "woodblock", "taiko", "toms", "syntom", "revcymb", "fx-fret", "fx-blow", "seashore", "jungle", "telephone", "helicptr", "applause", "ringwhsl" };

    std::string GMdrumnames[256] =
    { "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing",
      "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing",
      "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing", "nothing",
      "nothing", "nothing", "Bass Drum 2", "Bass Drum 1", "Side Stick/Rimshot", "Snare Drum 1", "Hand Clap", "Snare Drum 2",
      "Low Tom 2", "Closed Hi-hat", "Low Tom 1", "Pedal Hi-hat", "Mid Tom 2", "Open Hi-hat", "Mid Tom 1", "High Tom 2",
      "Crash Cymbal 1", "High Tom 1", "Ride Cymbal 1", "Chinese Cymbal", "Ride Bell", "Tambourine", "Splash Cymbal", "Cowbell",
      "Crash Cymbal 2", "Vibra Slap", "Ride Cymbal 2", "High Bongo", "Low Bongo", "Mute High Conga", "Open High Conga",
      "Low Conga", "High Timbale", "Low Timbale", "High Agogo", "Low Agogo", "Cabasa", "Maracas", "Short Whistle", "Long Whistle",
      "Short Gueiro", "Long Gueiro", "Claves", "High Wood Block", "Low Wood Block", "Mute Cuica", "Open Cuica", "Mute Triangle",
      "Open Triangle","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing",
      "nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing",
      "nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing",
      "nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing","nothing",
      "nothing","nothing",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea","no idea",
      "no idea","no idea","no idea","no idea","no idea","no idea"
      };

    // Default Mapping of Midi Instruments to Lotro Instruments
    unsigned int miditolotro[128] = {
    /* Pianos  0 - 8 */  0,1,0,1,0,0,1,1, /* Chromatic Percussion 9-16 */ 1,1,1,1,1,1,1,1, /* Organ  17-24   */ 4,4,4,6,6,6,6,6,
    /* Guitar  25-32 */  0,0,0,0,1,4,6,0, /* Bass 33-40                */ 2,2,2,2,2,2,2,2, /* Strings41-48   */ 5,4,3,3,4,1,1,2,
    /* Ensemble 49-56*/  5,4,5,4,4,3,6,0, /* Brass 57-64               */ 3,3,3,4,4,3,3,3, /* Reed 65-72     */ 3,3,3,3,4,4,4,4,
    /* Pipe     73-80*/  5,5,5,5,5,5,5,5, /* Synth Lead 81-88          */ 4,3,4,4,4,4,4,0, /* Synth Pad 89-96*/ 5,5,5,5,5,4,5,5,
    /* Synth   97-104*/  1,0,1,1,1,1,1,1, /* Ethnic 105-112            */ 1,0,0,0,1,6,6,6, /* Perc. 113-120  */ 0,0,0,0,2,2,2,1,
    /* Sound effects 121-128 */ 9,9,10,9,9,9,9,9};
    const int nInstruments = 22;
    std::string lotroinstruments[22] =
          {"lute", "harp", "theorbo", "horn", "clarinet", "flute", "bagpipes", "pipgorn", "drums",
     //      0      1        2         3         4          5        6           7         8
           "cowbell", "moor cowbell", "basic lute", "misty harp", "student", "lonely", "sprightly", "travellers", "bardic",
     //      9          10                 11            12         13          14           15         16          17
           "basicfiddle", "basson_flat", "basson_vib", "basson_stac"};
     //      18             19              20            21

     std::string lotroinstruments2[22] =
          {"Lute", "Harp", "Theorbo", "horn", "clarinet", "flute", "bagpipes", "pipgorn", "drums",
     //      0      1        2         3         4          5        6           7         8
           "cowbell", "moor cowbell", "basic lute", "misty harp", "student", "lonely", "sprightly", "travellers", "bardic",
     //      9          10                 11            12         13          14           15         16          17
           "basicfiddle", "basson_flat", "basson_vib", "basson_stac"};
     //      18             19              20            21

     // Lotro instruments
        std::string lotroinstruments3[22] = { "Lute", "Harp", "Theorbo", "Horn", "Clarinet", "Flute", "bagpipe", "Pibgorn", "drum",
                    "cowbell", "moor", "basic", "misty", "Student", "Lonely", "Sprightly", "Travellers", "Bardic", "BasicFiddle", "Basson_flat", "Basson_vib", "Basson_stac" };


//     const char * pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string volumenames[8] = {"+ppp+", "+pp+", "+p+", "+mp+", "+mf+", "+f+", "+ff+", "+fff+"};

     // Fade Out duration, used for estimation of sample load
     const int fadeout[22] = {
       34,  // lute
       34,  // harp
       29,  // theorbo
       7,   // horn
       7,   // clarinet
       7,   // flute
       3,   // bagpipes
       7,   // pibgorn
       24,  // drums have constant
       17,  // cowbell have constant
       17,  // moor bell
       34,  // crap lute
       34,  // harp
       7,   // student fiddle
       7,   // lonely fiddle
       7,   // sprightly
       38,  // travellers - yes this one is NASTY
       7,   // bardic
       7,    // basic
       7,   // bassonflat
       7,   // bassonvib
       7    // bassonstac
       };

       // type specifies if its added at the end of a tone or always constant duration (as for drums etc)
       const int fadeouttype[22] = {
       0,0,0,      // lute, harp, theorbo
       1,1,1,1,1,  // horn, clarinet, flute, bagpipes, pibgorn
       0,0,0,      // drums, cowbell, cowbell
       0, 0,       // crap lute, crap harp
       1, 1, 1,    // student, lonely, sprightly
       0,          // travellers
       1,1,        // bardic, basic
       1,1,1       // bassons: flat,vib,stac
       };

       // tonality conversion tables
       const int Cmajortominor[12] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8, 11, 10 };
       const int Cmajor[12]        = { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
       const int Cminor[12]        = { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0 };
       const int Cminor_h[12]      = { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1 };



        const int lotroinstrumentadd[22] = { 10, 20, 30, 60, 70, 50, 40, 90, 0, 80, 100 , 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210 };
        const int bardeninstrumentadd[22] = { 90, 10, 20, 50, 30, 40, 60, 100, 70, 80, 110 , 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220};

        //  Volume corrections U16.1  (in dB)
        const float instrumentvolumeoffset[22] = {0, 0.75, 3.75, -1.0, -2.75, -3.0, -2.0, -4.0, 2.75, 5.0, 12.0, -1.25, 0.25, 0, 0, 0 ,0 ,0 ,0 ,0,0,0};


        // Volume offsets per tone (in dB)
        const float toneoffsets[22][38] = {
        //lute
{-0.75,-1.25,0.0,0.0,0.5,0.5,0.0,0.25,0.25,0.25,-0.25,-1.25,-1.5,-1.25,-1.0,1.25,-0.5,-0.25,-1.0,-1.75,-1.75,-2.0,-0.5,-0.75,-1.25,0.5,0.25,2.25,1.75,1.75,2.0,1.75,1.0,1.25,1.5,1.75,1.25},
        //harp
{0.0,0.75,-0.25,0.75,1.5,0.0,0.25,-0.25,0.0,0.5,0.0,-0.25,0.5,-0.5,-1.5,-0.25,-0.5,-0.75,-0.25,0.0,2.25,0.0,0.5,1.75,0.25,-1.0,0.25,0.0,0.25,-0.75,-0.25,-0.25,1.5,-0.25,-0.5,1.75,0.5},
        //theorbo
{2.75,0.75,0.75,1.0,0.0,0.25,0.0,0.0,-0.5,0.0,1.25,0.0,0.25,0.5,1.25,0.0,0.0,1.0,0.0,0.0,-1.25,-0.75,1.25,0.25,0.0,-1.0,-0.75,-0.5,1.0,-0.25,-0.75,0.5,-0.25,0.75,1.25,-0.5,0.5},
        // horn
{-1.75,0.0,-1.5,0.0,-1.0,-1.0,1.25,-1.5,0.0,0.25,1.25,0.75,2.25,2.75,0.0,1.0,0.5,1.5,1.0,-1.25,-0.75,0.25,2.25,0.75,0.75,-0.75,-1.75,0.0,0.0,-0.25,-0.5,1.0,-1.0,-3.75,0.25,0.0,0.0},
//clarinet
 {-0.75,0.0,0.0,0.75,1.0,0.0,-1.75,-0.5,0.0,-1.5,-0.5,0.75,0.75,2.25,0.0,1.5,2.5,0.75,2.5,1.0,0.25,-0.75,0.0,0.25,0.25,0.0,-0.25,-0.5,-0.5,-2.0,-1.5,1.75,0.0,0.75,-3.5,0.75,0.5},
// flute
{0.0,0.75,1.0,0.0,2.0,1.75,1.0,1.75,1.0,-2.25,0.5,0.75,0.25,0.5,0.0,0.0,-1.5,-2.75,-3.75,-0.25,1.5,-0.75,1.0,0.75,0.75,-2.5,-0.5,-1.0,-2.25,-1.5,-1.0,-1.25,-2.5,0.0,0.25,0.5,1.25},
// bagpipes
{-0.5,-0.25,-2.5,0.75,0.75,-1.0,-0.25,-0.75,-1.25,-0.25,0.0,0.0,0.25,0.5,-1.0,0.0,-0.25,-2.0,2.75,1.75,2.25,2.0,2.25,2.5,2.75,2.25,0.0,0.0,-0.5,0.0,0.25,0.5,-1.5,0.25,-0.25,0.0,2.0},
// Pibgorn
{0.5,0.5,0.25,0.5,1.25,1.0,1.25,0.75,0.75,0.0,1.25,1.5,-0.75,0.0,0.5,0.5,0.0,0.0,0.5,0.25,-2.0,2.25,-0.5,-1.25,-3.25,-2.25,-1.75,-1.75,-2.25,-2.25,-1.25,-1.75,-3.5,0.5,-2.25,-3.5,-3.0},
//Drums
{1.75,2.0,-0.5,-3.5,5.5,-1.5,2.75,-3.75,-0.5,-3.25,1.25,-1.0,-2.0,0.25,-0.25,-3.0,-2.5,-0.25,0.5,2.25,-1.0,0.25,0.0,1.0,0.0,-2.75,0.5,1.5,-2.0,1.25,2.0,-0.5,2.0,0.0,-1.75,0.5,-4.0},
// Cowbell
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// moor bell
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// crap lute
{-4.0,-1.25,-2.5,-3.5,0.25,0.25,0.0,0.0,-0.25,0.25,-0.25,-0.75,-0.25,-0.75,-0.5,-0.25,0.0,1.5,0.25,-0.75,-0.5,-1.25,0.5,-0.25,0.5,2.0,1.75,3.0,3.0,2.0,3.0,2.0,2.0,2.0,2.75,0.0,3.0},
// mmharp
{-0.5,0.25,0.75,0.25,0.0,0.0,0.5,0.0,-0.25,-0.5,2.0,0.75,2.25,-0.75,0.25,-0.25,-1.25,-1.25,0.25,-0.25,0.5,0.75,2.5,1.5,2.75,0.5,0.25,-0.5,-0.75,-3.75,-3.25,0.0,-3.0,-1.75,-2.25,-0.5,0.0},
// student fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// lonely fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// sprightly fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//travellers fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// bardic fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// basic fiddle
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// basson_flat
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//basson_vib
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// basson_stac
{0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };


// Note ranges
int noteranges[22][2] = {
               {0,36},  // Lute
               {0,36},  // Harp
               {0,36},  // Theorbo
               {0,36},  // Horn
               {0,36},  // Clarinet
               {0,36},  // Flute
               {0,36},  // Bagpipes
               {0,36},  // Pipgorn - it might go up too high, but for me sounds reasonable
               {0,128}, // Drums
               {0,36},  // Cowbell
               {0,36},  // Moor Cowbell
               {0,36},  // crap lute
               {0,36},  // mm harp
               {0,36},   // student fiddle
               {0,36},   // lonely fille
               {0,36},   // sprightly fiddle
               {0,36},   // travellers
               {0,36},  // bardic
               {0,36},   // basicfiddle
               {0,36},  // bassonflat
               {0,36},  // bassonvib
               {0,36}   // bassonstac
              };

// string split function
std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      if (token!="")
       tokens.push_back(token);
   }
   return tokens;
}

std::string maketime( double mseconds )
{
    std::stringstream output;
    double minutes = mseconds / 1000000.0;
    double remain = (minutes - static_cast<int>(minutes))*60;

    if (  remain >= 10.0  ){
     output << static_cast<int>(minutes)<<":" << remain;
    }
    else{
     output << static_cast<int>(minutes)<<":0" << remain;
    }
    return output.str();
}

std::string readline( std::ifstream & inputfile )
{
    std::string output;
    std::getline(inputfile, output);
    return output;
}

std::vector< std::vector < int > > AppendIU ( std::vector<std::vector < int > > iulist, std::vector< int > ulist )
{
    std::vector < std::vector < int > > newlist;

    // new vector is one element larger than old
    newlist.resize( iulist.size()+1 );

    // copy old vector
    for (unsigned int i=0; i < iulist.size(); i++)
    {
        newlist[i].resize(iulist[i].size());
        for (unsigned int j = 0; j < iulist[i].size(); j++)
            newlist[i][j] = iulist[i][j];
    }
    // put in new values
    newlist[ iulist.size() ].resize(ulist.size());
    for (unsigned int j = 0; j < ulist.size(); j++)
        newlist[iulist.size()][j] = ulist[j];
    return newlist;
}

std::vector<int> AppendI( std::vector<int> inputlist, int value)
{
    std::vector<int> newlist;
    newlist.resize(inputlist.size()+1);
    for (unsigned int i=0; i < inputlist.size(); i++)
        newlist[i] = inputlist[i];
    newlist[inputlist.size()]=value;
    return newlist;
}



std::stringstream m_log;

// greatest common divisor
int gcd(int a, int b)
{
   if (b == 0)
      return a;
   return gcd(b, a % b);
}

// calculate duration string for these 2 numbers
std::string durationstring(double a, int b)
{
  std::stringstream answer;
  std::string answer2;
  int divisor = gcd(static_cast<int>(a), b);
  int aa = static_cast<int>(a) / divisor;
  int bb =  b / divisor;
  if (aa == 1)
  {
     answer << "/" << bb;
  }
  else
  {
     answer << aa << "/" << bb;
  }
  if (bb == 1)
  {
      answer << aa ;
  }
  answer2 = answer.str();
  return answer2;
}

bool dequal( double a, double b)
{
    bool retval = false;
    if ( a < b + 1)
       if ( a > b - 1)
          retval = true;
    return retval;
}

#endif
