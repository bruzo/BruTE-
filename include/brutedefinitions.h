#ifndef BRUTEDEFS_H
#define BRUTEDEFS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <deque>
#include <map>


typedef std::tuple< int64_t, int64_t, int64_t, int32_t, int32_t, float > ToneTuple;


    const double timetoticks = 0.60476973728946;

    const std::vector<uint16_t> cmajor = {1,0,1,0,1,1,0,1,0,1,0,1};

    const std::vector<size_t> cmajortominor = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8, 11, 10 };


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

     std::vector<std::string> GMDrumNames =
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

      // C, = 36   C = 48  c = 60      // C-D = 2 // C-E = 4 // C-F = 5 // C-G = 7 // C-A = 9 // C-B =11

      // C, = 0   C = 12 c = 24
      /*
      std::vector<std::string> LotroDrumSampleNames =
      {
          "Bass (^G)\t20", "Bass Open (^A)\t22", "Bass Slap 1 (^C)\t13", "Bass Slap 2 (D)\t14", "Bend High Up (f)\t29",
          "Bend Low Up (d)\t26", "Bend Mid Down (e)\t28", "Bongo High (D,)\t2", "Bongo Low (a)\t33",
          "Conga High 1 (C,)\t0", "Conga High 2 (^a)\t34", "Conga Low (g)\t31", "Conga Mid (b)\t35",
          "Muted 1 (F,)\t7", "Muted 2 (^c)\t25", "Muted Mid (C)\t12", "Rattle 1 (G)\t19",
          "Rattle 2 (B)\t23", "Rattle 3 (c)\t24", "Rattle Long (A)\t21", "Rattle Short 1 (^C,)\t1",
          "Rattle Short 2 (^F,)\t6", "Rattle Short 3 (^G,)\t8", "Rim Shot 1 (^D)\t15", "Rim Shot 2 (F)\t17",
          "Slap 1 (^D,)\t3", "Slap 2 (E,)\t4", "Slap 3 (E)\t14", "Slap 4 (^F)\t 18",
          "Slap 5 (^f)\t30", "Slap 6 (^g)\t32", "Slap 7 (c')\t36",
          "Tambourine (^A,)\t10", "Tom High 1 (G,)\t7", "Tom High 2 (A,)\t9", "Tom Mid 1 (B,)\t11", "Tom Mid 2 (^d)\t27"
      };*/

      std::vector<std::string> LotroDrumSampleNames =
      {
          "No Direct Mapping",
          "Conga High 1 (C,) 0",
          "Rattle Short 1 (^C,) 1",
          "Bongo High (D,) 2",
          "Slap 1 (^D,) 3",
          "Slap 2 (E,) 4",
          "Muted 1 (F,) 5",
          "Rattle Short 2 (^F,) 6",
          "Tom High 1 (G,) 7",
          "Rattle Short 3 (^G,) 8",
          "Tom High 2 (A,) 9",
          "Tambourine (^A,) 10",
          "Tom Mid 1 (B,) 11",
          "Muted Mid (C) 12",
          "Bass Slap 1 (^C) 13",
          "Bass Slap 2 (D) 14",
          "Rim Shot 1 (^D) 15",
          "Slap 3 (E) 16",
          "Rim Shot 2 (F) 17",
          "Slap 4 (^F) 18",
          "Rattle 1 (G) 19",
          "Bass (^G) 20",
          "Rattle Long (A) 21",
          "Bass Open (^A) 22",
          "Rattle 2 (B) 23",
          "Rattle 3 (c) 24",
          "Muted 2 (^c) 25",
          "Bend Low Up (d) 26",
          "Tom Mid 2 (^d) 27",
          "Bend Mid Down (e) 28",
          "Bend High Up (f) 29",
          "Slap 5 (^f) 30",
          "Conga Low (g) 31",
          "Slap 6 (^g) 32",
          "Bongo Low (a) 33",
          "Conga High 2 (^a) 34",
          "Conga Mid (b) 35",
          "Slap 7 (c') 36",
      };

      std::vector<std::string> LotroStudentFiddleSampleNames =
      {
          "No Direct Mapping",
          "Strings (C,) 0",
          "Knock (^C,) 1",
          "Scratch (D,) 2",
          "None (^D,) 3",
          "None (E,) 4",
          "None (F,) 5",
          "None (^F,) 6",
          "None (G,) 7",
          "None (^G,) 8",
          "None (A,) 9",
          "None (^A,) 10",
          "None (B,) 11",
          "(C) 12",
          "(^C) 13",
          "(D) 14",
          "(^D) 15",
          "(E) 16",
          "(F) 17",
          "(^F) 18",
          "(G) 19",
          "(^G) 20",
          "(A) 21",
          "(^A) 22",
          "(B) 23",
          "(c) 24",
          "(^c) 25",
          "(d) 26",
          "(^d) 27"
          "(e) 28",
          "(f) 29",
          "(^f) 30",
          "(g) 31",
          "(^g) 32",
          "(a) 33",
          "(^a) 34",
          "(b) 35",
          "(c') 36",
      };
      std::vector<std::string> LotroToneSampleNames =
      {
          "No Direct Mapping",
          "(C,) 0",
          "(^C,) 1",
          "(D,) 2",
          "(^D,) 3",
          "(E,) 4",
          "(F,) 5",
          "(^F,) 6",
          "(G,) 7",
          "(^G,) 8",
          "(A,) 9",
          "(^A,) 10",
          "(B,) 11",
          "(C) 12",
          "(^C) 13",
          "(D) 14",
          "(^D) 15",
          "(E) 16",
          "(F) 17",
          "(^F) 18",
          "(G) 19",
          "(^G) 20",
          "(A) 21",
          "(^A) 22",
          "(B) 23",
          "(c) 24",
          "(^c) 25",
          "(d) 26",
          "(^d) 27"
          "(e) 28",
          "(f) 29",
          "(^f) 30",
          "(g) 31",
          "(^g) 32",
          "(a) 33",
          "(^a) 34",
          "(b) 35",
          "(c') 36",
      };


      std::vector<std::string> ABCStyleNames =
      {
          "Rocks",
          "TSO",
          "Meisterbarden"
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

    std::vector<std::string> rockstyleinstrumentnames =
    {
        "lute of ages", "basic harp", "theorbo", "horn", "clarinet", "flute", "bagpipes", "pipgorn", "drums",
     //      0      1        2         3         4          5        6           7         8
           "basic cowbell", "moor cowbell", "basic lute", "misty harp", "student fiddle", "lm fiddle", "sprightly fiddle", "travel fiddle", "bardic fiddle",
     //      9                10                 11            12          13               14            15                  16          17
           "basic fiddle", "basic bassoon", "lm bassoon", "bruesque bassoon"
           // 18               19               20             21
    };

    std::vector<std::string> TSOtyleinstrumentnames =
    {
        "Lute of the Ages", "Basic Harp", "Basic Theorbo", "Basic Horn", "Basic Clarinet", "Basic Flute", "Bagpipes", "Pipgorn", "Drums",
     //      0      1        2         3         4          5        6           7         8
        "Basic Cowbell", "Moor Cowbell", "Basic Lute", "Misty M Harp", "Student Fiddle", "Lonely M Fiddle", "Sprightly Fiddle", "Travel. T. Fiddle", "Bardic Fiddle",
     //      9          10                 11            12         13          14           15         16          17
        "Basic Fiddle", "Basic Bassoon", "Lonely M Bassoon", "Bruesque Bassoon"
    };

    std::vector<std::string> Maestrostyleinstrumentnames =
    {
        "Lute of Ages", "Basic Harp", "Basic Theorbo", "Basic Horn", "Basic Clarinet", "Basic Flute", "Basic Bagpipe", "Basic Pipgorn", "Basic Drum",
     //      0      1        2         3         4          5        6           7         8
        "Basic Cowbell", "Moor Cowbell", "Basic Lute", "Misty Mountain Harp", "Student Fiddle", "Lonely Mountain Fiddle", "Sprightly Fiddle", "Traveller's Trusty Fiddle", "Bardic Fiddle",
     //      9          10                 11            12         13          14           15         16          17
        "Basic Fiddle", "Basic Bassoon", "Lonely Mountain Bassoon", "Brusque Bassoon"
    };

    std::vector<std::vector<std::string>> abcnamingstyleinstrumentnames =
    {
        rockstyleinstrumentnames, TSOtyleinstrumentnames, TSOtyleinstrumentnames, Maestrostyleinstrumentnames
    };


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

    std::string lotroinstruments_formal[22] =
          {"Lute of the Ages", "Basic Harp", "Theorbo", "Horn", "Clarinet", "Flute", "Bagpipes", "Pipgorn", "Drums",
     //      0      1        2         3         4          5        6           7         8
           "Cowbell", "Moor Cowbell", "Basic Lute", "Misty M. Harp", "Student Fiddle", "Lonely M. Fiddle", "Sprightly Fiddle", "Travellers Tr.", "Bardic Fiddle",
     //      9          10                 11            12         13          14           15         16          17
           "Basic Fiddle", "Basic Basson", "Lonely M. Basson", "Brusque Basson"};
     //      18             19              20            21
//     const char * pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string volumenames[8] =      {"+ppp+", "+pp+", "+p+", "+mp+", "+mf+", "+f+", "+ff+", "+fff+"};
    // std::string fullvolumenames[10] = {"+pppp+", "+ppp+", "+pp+", "+p+", "+mp+", "+mf+", "+f+", "+ff+", "+fff+", "+ffff+"};



     std::vector<float> pitchgains = {0.2, 0.2, 0.28, 0.37, 0.46, 0.55, 0.64, 0.73, 0.78, 0.78};
     std::vector<float> relativegain = {1, 1.25, 0.56, 1.25, 0.95, 0.95, 0.95, 0.95, 1.25, 1., 1.25, 0.55, 0.74, 1.  , 1.25, 0.6, 0.8, 1.25, 1.25, 1.25, 1.25, 1.25, 1.25};
                                      //1  2     3      4    5    6     7     8      9   10 11  12    13     14    15    16  17   18    19     20   21
                            //      1 2 3 4   5   6   7   8   9 10  11  12 13  14     15    16   17   18     19   20    21
     std::vector<float> fadeouts = {0,0,0,0.2,0.2,0.2,0.2,0.2,0,0  ,0  ,0  ,0  ,0.2  ,0.2  ,0.4, 0   ,0.2   ,0.2 ,0.2,  0.2,  0.5};

     std::vector < float > relvol = { 1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  };


     // time of attack in samples at 44.1KHz       lute of ages    harp          theorbo      horn        clarinet      flute        bagpipes       pibgorn
     std::vector<std::vector<uint32_t>> adsr = {{  0, 1000000  }, {0, 100000}, {0, 100000} , {0, 1000000}, {0, 1000000}, {0, 1000000}, {0, 1000000} , {0, 1000000},
                                             //    drum         cowbell      moor bell      basic lute
                                                {0, 1000000},  {0, 1000000}, {0, 1000000}, {0, 1000000}
                                                    };

     // time of attack in samples at 44.1KHz       lute of ages    harp          theorbo      horn        clarinet      flute        bagpipes       pibgorn
     std::vector<std::vector<float>> adsr_v =  { {1.0,   1.0}   , {1.0, 1.0} , {1.0, 1.0}, {1.0, 1.0} , {1.0, 1.0} , {1.0, 1.0} , {1.0, 1.0}  , {1.0, 1.0},
     //                                          drum       cowbell         moor bell       basic lute
                                                {1.0, 1.0}, {1.0, 1.0},    {1.0, 1.0},     {1.0, 1.0}

       };

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

/*
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
*/

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

// Midi Generation Information
std::string abcpitches[58] = {   "C,","^C,","_D,","D,","^D,","_E,","E,","^E,","_F,","F,","^F,","_G,","G,","^G,","_A,","A,","^A,","_B,","B,",
                                 "C" ,"^C" ,"_D" ,"D" ,"^D" ,"_E" ,"E" ,"^E" ,"_F" ,"F" ,"^F" ,"_G" ,"G" ,"^G" ,"_A" ,"A" ,"^A" ,"_B" ,"B" ,
                                 "c" ,"^c" ,"_d" ,"d" ,"^d" ,"_e" ,"e" ,"^e" ,"_f" ,"f" ,"^f" ,"_g" ,"g" ,"^g" ,"_a" ,"a" ,"^a" ,"_b" ,"b" , "'c"};

int abcpitchvalues[58] =     {     36,   37,   37,  38,   39,   39,  40,   41, 40  , 41 ,   42,   42,  43,   44,   44,  45,   46,   46,  47,
                                   48,   49,   49,  50,   51,   51,  52,   53, 40  , 53 ,   54,   54,  55,   56,   56,  57,   58,   58,  59,
                                   60,   61,   61,  62,   63,   63,  64,   65, 40  , 65 ,   66,   66,  67,   68,   68,  69,   70,   70,  71,  72};


std::map<std::string,int>InstrumentMidiChannels =
{
    {"lute", 24},
    {"Lute", 24},
    {"Harp", 46},
    {"harp", 46},
    {"Theorbo", 32},
    {"theorbo", 32},
    {"Drums", 118},
    {"drums", 118},
    {"Cowbell", 115},
    {"cowbell", 115},
    {"Moor Cowbell", 114},
    {"moor cowbell", 114},
    {"moorbell", 114},
    {"Pipgorn", 84},
    {"pipgorn", 84},
    {"misty_harp", 27},
    {"mmharp", 27},
    {"misty harp", 27},
    {"Basic Lute", 25},
    {"basic lute", 25},
    {"basiclute", 25},
    {"brokenlute", 25},
    {"lute of ages", 24},
    {"agelute", 24},
    {"Lute of Ages", 24},
    {"Clarinet", 71},
    {"clarinet", 71},
    {"Flute", 73},
    {"flute", 73},
    {"Horn", 69},
    {"horn", 69},
    {"bagpipe", 109},
    {"bagpipes", 109},
    {"Bagpipes", 109},
    {"Bagpipes", 109},
    {"student fiddle", 60},
    {"student", 60},
    {"Student Fiddle", 60},
    {"lonely", 41},
    {"Lonely Mountain Fiddle", 41},
    {"Lonely", 41},
    {"sprightly", 49},
    {"Sprightly", 49},
    {"Sprightly Fiddle", 49},
    {"Travellers Trusty Fiddle", 45},
    {"travellers", 45},
    {"Travellers", 45},
    {"travellers trusty fiddle", 45},
    {"bardic", 42},
    {"Bardic", 42},
    {"Bardic Fiddle", 42},
    {"bardic fiddle", 42},
    {"basicfiddle", 43},
    {"BasicFiddle", 43},
    {"Basson_flat", 77},
    {"basson_flat", 77},
    {"Basson_vib", 76},
    {"basson_vib", 76},
    {"basson_stac", 75},
    {"Basson_stac", 75}
};


std::map<std::string,int>InstrumentMidiNumbers =
{
    {"lute", 0},
    {"Lute", 0},
    {"Harp", 1},
    {"harp", 1},
    {"Theorbo", 2},
    {"theorbo", 2},
    {"Drums", 8},
    {"drums", 8},
    {"Cowbell", 9},
    {"cowbell", 9},
    {"Moor Cowbell", 10},
    {"moor cowbell", 10},
    {"moorbell", 10},
    {"Pipgorn", 7},
    {"pipgorn", 7},
    {"misty_harp", 12},
    {"mmharp", 12},
    {"misty harp", 12},
    {"Basic Lute", 11},
    {"basic lute", 11},
    {"basiclute", 11},
    {"brokenlute", 11},
    {"lute of ages", 0},
    {"agelute", 0},
    {"Lute of Ages", 0},
    {"Clarinet", 4},
    {"clarinet", 4},
    {"Flute", 5},
    {"flute", 5},
    {"Horn", 3},
    {"horn", 3},
    {"bagpipe", 6},
    {"bagpipes", 6},
    {"Bagpipes", 6},
    {"Bagpipes", 6},
    {"student fiddle", 13},
    {"student", 13},
    {"Student Fiddle", 13},
    {"lonely", 14},
    {"Lonely Mountain Fiddle", 14},
    {"Lonely", 14},
    {"sprightly", 15},
    {"Sprightly", 15},
    {"Sprightly Fiddle", 15},
    {"Travellers Trusty Fiddle", 16},
    {"travellers", 16},
    {"Travellers", 16},
    {"travellers trusty fiddle", 16},
    {"bardic", 17},
    {"Bardic", 17},
    {"Bardic Fiddle", 17},
    {"bardic fiddle", 17},
    {"basicfiddle", 18},
    {"BasicFiddle", 18},
    {"Basson_flat", 19},
    {"basson_flat", 19},
    {"Basson_vib", 20},
    {"basson_vib", 20},
    {"basson_stac", 21},
    {"Basson_stac", 21}
};

/*
std::map<std::string, int> MidiVelocities =
{
              {"+pppp+" , 51},
              {"+ppp+", 51},
              {"+pp+", 64},
              {"+p+", 73},
              {"+mp+", 82},
              {"+mf+", 89},
              {"+f+", 96},
              {"+ff+", 102},
              {"+fff+", 105},
              {"+ffff+", 105}
};
*/

std::map<std::string, int> VelocityValues =
{
              {std::string("+pppp+") , 0},
              {std::string("+ppp+"), 1},
              {std::string("+pp+"), 2},
              {std::string("+p+"), 3},
              {std::string("+mp+"), 4},
              {std::string("+mf+"), 5},
              {std::string("+f+"), 6},
              {std::string("+ff+"), 7},
              {std::string("+fff+"), 8},
              {std::string("+ffff+"), 9}
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
       tokens.emplace_back(token);
   }
   return tokens;
}


/*
std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens(0);
   std::string token = "";

   for (size_t i = 0; i < s.size(); i++ )
   {
       if (s[i] != delimiter)
       {
           token = token + s[i];
       }
       else
       {
           if (token!="")
           {


            tokens.push_back(token);
            token = "";
           }
       }
   }
   return tokens;
}
*/

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

std::vector< std::vector < float > > AppendFU( std::vector< std::vector<float> > iulist, std::vector<float> ulist)
{
   std::vector< std::vector < float >> newlist;
   // new vector is one element larger than old
   newlist.resize(iulist.size()+1);
   // copy old vector
   for (unsigned int i=0; i < iulist.size(); i++)
   {
      newlist[i].resize(iulist[i].size());
      for (unsigned int j = 0; j < iulist[i].size(); j++)
         newlist[i][j] = iulist[i][j];
   }
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

std::vector<float> AppendF( std::vector<float> inputlist, float value)
{
    std::vector<float> newlist;
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

/*
const static unsigned char MinimalSoundFont[] =
{
	#define TEN0 0,0,0,0,0,0,0,0,0,0
	'R','I','F','F',220,1,0,0,'s','f','b','k',
	'L','I','S','T',88,1,0,0,'p','d','t','a',
	'p','h','d','r',76,TEN0,TEN0,TEN0,TEN0,0,0,0,0,TEN0,0,0,0,0,0,0,0,255,0,255,0,1,TEN0,0,0,0,
	'p','b','a','g',8,0,0,0,0,0,0,0,1,0,0,0,'p','m','o','d',10,TEN0,0,0,0,'p','g','e','n',8,0,0,0,41,0,0,0,0,0,0,0,
	'i','n','s','t',44,TEN0,TEN0,0,0,0,0,0,0,0,0,TEN0,0,0,0,0,0,0,0,1,0,
	'i','b','a','g',8,0,0,0,0,0,0,0,2,0,0,0,'i','m','o','d',10,TEN0,0,0,0,
	'i','g','e','n',12,0,0,0,54,0,1,0,53,0,0,0,0,0,0,0,
	's','h','d','r',92,TEN0,TEN0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0,49,0,0,0,34,86,0,0,60,0,0,0,1,TEN0,TEN0,TEN0,TEN0,0,0,0,0,0,0,0,
	'L','I','S','T',112,0,0,0,'s','d','t','a','s','m','p','l',100,0,0,0,86,0,119,3,31,7,147,10,43,14,169,17,58,21,189,24,73,28,204,31,73,35,249,38,46,42,71,46,250,48,150,53,242,55,126,60,151,63,108,66,126,72,207,
		70,86,83,100,72,74,100,163,39,241,163,59,175,59,179,9,179,134,187,6,186,2,194,5,194,15,200,6,202,96,206,159,209,35,213,213,216,45,220,221,223,76,227,221,230,91,234,242,237,105,241,8,245,118,248,32,252
};
*/

/*
typedef struct STEREO_WAV_HEADER {
  // RIFF Chunk Descriptor
  uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
  uint32_t ChunkSize;                     // RIFF Chunk Size
  uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
  // "fmt" sub-chunk
  uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
  uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
  uint16_t AudioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
                            // Mu-Law, 258=IBM A-Law, 259=ADPCM
  uint16_t NumOfChan = 2;   // Number of channels 1=Mono 2=Sterio
  uint32_t SamplesPerSec = 44100;   // Sampling Frequency in Hz
  uint32_t bytesPerSec = 44100 * 4; // bytes per second
  uint16_t blockAlign = 4;          // 2=16-bit mono, 4=16-bit stereo
  uint16_t bitsPerSample = 16;      // Number of bits per sample
  // "data" sub-chunk
  uint8_t Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
  uint32_t Subchunk2Size;                        // Sampled data length
} stereo_wav_hdr;
*/

    std::vector<std::vector<int>> oggpitchnumbers=
    {
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36},
        {36},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
        {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72}
    };


int WhichInstrumentNumber(std::string input)
{
      int myinstrument = -1;
      for (auto it = InstrumentMidiNumbers.begin(); it != InstrumentMidiNumbers.end(); ++it)
         if ( input.find(it->first) != std::string::npos )
             return it->second;
      return myinstrument;
}

int CheckForInstrument(std::string input)
{
   int myinstrument = -1;
   for (size_t j = 0; j < abcnamingstyleinstrumentnames.size(); j++)
   {
   for (size_t i = 0; i < abcnamingstyleinstrumentnames[j].size(); i++)
      {
         if (  input.find(abcnamingstyleinstrumentnames[j][i]) != std::string::npos )
         {
           myinstrument = i;
         }
      }
   }
   return myinstrument;
}

int GetABCInstrumentFromTLine(std::string line)
{
   int returnvalue = -1;

   int blainstrument = CheckForInstrument(line);
   if (blainstrument > -1)
   {
      returnvalue = blainstrument;
   }
   else
   {
      // we only used instruments defined between [] in the T line
      std::string myinstrument = line.substr(line.find_last_of("[")+1,line.find_last_of("]") );
      myinstrument.pop_back();
      int oldinstrument = WhichInstrumentNumber(myinstrument);
      if (oldinstrument > -1)  { returnvalue = oldinstrument; }
      else {returnvalue = 0;}
   }
   return returnvalue;
}



double EvaluateDurationString(std::string input)
{

    //std::cout << "Eval String " << input <<  "   " << std::endl;
    // if the length is 0 this is easy
    if (input.length() == 0) return 1.0;

    // Get the /////// out of the way
    if ((input.length() == 1)&&(input=="/")) return 0.5;
    if ((input.length() == 2)&&(input=="//")) return 0.25;
    if ((input.length() == 3)&&(input=="///")) return 0.125;
    if ((input.length() == 4)&&(input=="////")) return 0.125*0.5;
    if ((input.length() == 5)&&(input=="/////")) return 0.125*0.25;
    if ((input.length() == 6)&&(input=="//////")) return 0.125*0.125;


    // Now Check if this is a fraction
    if (input.find('/') !=  std::string::npos)   // this is a fraction
    {
        std::vector<std::string> twovalues = split(input, '/');
        if (twovalues.size()>1)
        {
            return ( 1.0 * std::stoi(twovalues.at(0)) / (1.0 * std::stoi(twovalues.at(1))) );
        }
        else
        {
            return (( 1.0 ) / (1.0 * std::stoi(twovalues.at(0))) );
        }
    }
    else  // this is just a number
    {
       // std::cout << "Returning a " << std::stoi(input) << std::endl;;
        return std::stoi(input);
    }
    // we have no idea what this means .... we're returning a full tone ...
    return 1.;
}


double ChordDuration(std::string input)
{
   // std::cout << input << std::endl;
    std::string myinput = input;
    std::vector< char > forbidden = { 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'A', 'a', 'B', 'b', '^', '_', '[', ']', '=', ',', '-', '\'', 'z' };
    // first Replace all Characters with spaces

    size_t digits = 0;
    size_t divisors = 0;
    for (size_t i = 0; i < myinput.length(); i++)
    {
        for (size_t j = 0; j < forbidden.size(); j++)
        if ( myinput[i] == forbidden[j])
        {
            myinput[i] = ' ';
        }
        if (isdigit(myinput[i])) digits++;
        if (myinput[i]=='/') divisors++;
    }
    if ((digits == 0)&&(divisors==0))
    {
     //   std::cout << "No Digits, returning 1.0 "<< std::endl;
        return 1.0;
    }
    //then split into an array by the spaces
    std::string myduration = split(myinput, ' ')[0];
  //  std::cout << "Querying:" << myduration << std::endl;
    return EvaluateDurationString(myduration); // and then just use the first duration
}

// Find the number of occurances of substring in strfull
size_t Frequency_Substr(std::string strfull, std::string substring)
{
    size_t counter = 0;
    size_t pos = 0;
    while ((pos = strfull.find(substring, pos)) != std::string::npos)
    {
       ++counter;
       pos += substring.length();
    }
    return counter;
}

inline bool IsBreak(std::string input)
{
   return (!input.empty() && input[0] == 'z') ? true : false;
}


std::vector<std::string> ABCTextArray(std::string input, char separator)
{
    std::vector<std::string> returntext;

    std::string tempstr;
    bool firstchar = true;
    for (char c : input)
    {
        if (c == separator)
        {
            if (!firstchar)
            {
                tempstr += separator;
            }
            returntext.push_back(tempstr);
            tempstr.clear();
            firstchar = true;
        }
        else
        {
            tempstr += c;
            firstchar = false;
        }
    }
    if (!tempstr.empty())
    {
        returntext.push_back(tempstr);
    }
    return returntext;
}


std::vector<std::string> ABCTextArray(const std::string& input, const std::string& separator)
{
    std::vector<std::string> returntext;

    size_t startpos = 0;
    size_t endpos = input.find(separator);

    while (endpos != std::string::npos) {
        returntext.push_back(input.substr(startpos, endpos - startpos));
        startpos = endpos;
        endpos = input.find(separator, startpos + separator.length());
    }

    returntext.push_back(input.substr(startpos));

    return returntext;
}

void ABCSplitHeaderBody(std::stringstream& alllines, std::vector< std::string>& mytracklines, std::vector<std::string>& mytrackheader)
{
   std::string line;
   mytracklines.resize(0);
   mytrackheader.resize(0);
   while ( std::getline(alllines, line) )
   {
      if ((line[0]!='%')&&(line.size() > 0))
      {
         if (( line.size()>1 )&&(line[1]==':' ))
         {
            mytrackheader.push_back(line);
         }
         else
         {
            if (line.size()>0)
            {

            auto lines = split(line, ' ');

            for ( auto element : lines)
            {
               if (element.size() > 0)
               {
                 if (element !="|")
                 {
                    if (!((element.size()==2)&&(element =="|]")))
                    {
                        if (!((element.size()==2)&&(element =="\n")))
                        {
                         //   std::cout << element << std::endl;
                            if (element[0] == '\t')
                            {
                               mytracklines.push_back(element.substr(1));
                            }
                            else
                            {
                               mytracklines.push_back(element);
                            }
                        }
                    }
                 }
               }
            }
            }
         }
     }
   }
}

/*
inline bool IsVelchange(std::string input)
{
    auto it = VelocityValues.find(input);
    
    if (it == VelocityValues.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}
*/


inline bool IsVelchange(std::string input)
{
	if ( input[0] == '+' )
	{
	   return true;
	}
	else
	{
		return false;
	}
}

inline int Velocity(std::string input)
{
  return VelocityValues[input];
}

double BreakDuration(std::string input)
{
 //  std::string onlyduration = input.erase(0,1);
 //  return EvaluateDurationString(onlyduration);
 return EvaluateDurationString(input.substr(1));
}

std::deque<int> GetPitches(std::string input)
{
    std::string myinput = input;
    std::vector< char > forbidden = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/', '[', ']'};
    // first replace all non-pitch information ( duration and chord brackets with spaces
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

    return returnvalue;
}

bool IsLetter(char input)
{
    const std::vector<char> pitchchars =    {'C','D','E','F','G','A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b'};
    bool returnvalue = false;
    for (size_t i = 0; i < pitchchars.size(); i++) if (pitchchars[i]==input) returnvalue = true;
    return returnvalue;
}

int LetterIndex(char input)
{
    int returnvalue = -1;
    const std::vector<char> pitchchars =    {'C','D','E','F','G','A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b'};
    for (size_t i = 0; i < pitchchars.size(); i++) if (pitchchars[i]==input) returnvalue = i;
    if ( returnvalue> -1)
    {
        return (returnvalue%8);
    }
    else
    {
        return returnvalue;
    }
}

bool IsOctave(char input)
{
    if (input == ',') return true;
    if (input == '\'') return true;
    return false;
}

bool IsRel(char input)
{
    bool returnvalue = false;
    if (input=='^') returnvalue = true;
    if (input=='=') returnvalue = true;
    if (input=='_') returnvalue = true;
    return returnvalue;
}


int16_t Charvalue(char input)
{
    const std::vector<char> pitchchars =     {'C','D','E','F','G','A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b', '^', '_', ',', '\'', '-' };
    const std::vector<int16_t> pitchval =    {0  ,2  ,4  ,5  ,7  ,9  ,11  ,12  ,14  ,16  , 17 , 19 ,  21,  23,  1 , -1, -12 , 12, 100  };
    for (size_t i = 0; i < pitchchars.size(); i++) if (pitchchars[i] == input) return pitchval[i];
    return 0;
}

/*
std::vector<int16_t> GetPitches3(std::string input)
{

    std::vector<int16_t) valueline( input.size() );
    for (size_t i = 0; i < input.size(); i++) valueline[i] = Charvalue(input[i]);


    size_t pos = 0;
    if (input[pos]=="[") pos+=1;

    while (pos < input.size())
    {
        // check for modchars move only if one of those is found
        if ( input [pos] == modchars[0])
        {
            pitch = pitch + modpitch[0];
            pos++;
        }
        else
        {
            if (input[pos] == modchars[1])
            {
                pitch = pitch + modpitch[1];
                pos++;
            }
        }

        // check for Letter
        bool found = false;
        size_t index = 0;
        for (size_t j = 0;  < pitchchars.size(); j++)
        {
            if (input[pos] == pitchchars[j]){found = true; index=j;}
        }
        if (found)
        {
            pitch = pitch + pitchval[index];
            pos++;
        }

        // check for octave
        if (input[pos] == ochars[0])
        {
            pitch = pitch + ovals[0];
            pos++;
        }
        else
        {
            if (input[pos] == ochars[1])
            {
                pitch = pitch + ovals[1];
                pos++;
            }
        }


    }
}*/

std::vector<int16_t> GetPitches2(std::string input)
{
    //std::cout <<"Input:" <<  input << std::endl;
    std::string myinput = input;
    std::vector< char > forbidden = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/', '[', ']', 'z'};
    // first replace all non-pitch information ( duration and chord brackets with spaces
    for (size_t i = 0; i < myinput.length(); i++)
    {
        for (size_t j = 0; j < forbidden.size(); j++)
            if (myinput[i]==forbidden[j])
               myinput[i] = ' ';
    }
    //std::cout <<"Input adjusted " << myinput << std::endl;
    // now make sure continuation signs are distinguishable
    for (size_t i=0; i < myinput.length(); i++)
    {
        if ( myinput[i]=='-' ) myinput.insert(i+1, " ");
    }

    // now we need to make sure that tones without a duration (1) are splitted
    for (size_t i=0; i < myinput.length()-1; i++)
    {
        if ( IsLetter(myinput[i]) && IsLetter(myinput[i+1]))
             {
                 myinput.insert(i+1, " ");
             }
        if ( IsOctave(myinput[i]) && IsLetter(myinput[i+1]))
            {
                myinput.insert(i+1, " ");
            }
        if ( (myinput[i]=='-') && IsLetter(myinput[i+1]))
        {
            myinput.insert(i+1, " ");
        }
        if (  IsOctave(myinput[i]) && (myinput[i+1]=='-') )
        {
            myinput.insert(i+1," ");
        }
        if ( IsLetter(myinput[i]) && (myinput[i+1]=='-'))
        {
            myinput.insert(i+1," ");
        }
        if ( IsLetter(myinput[i]) && (IsRel( myinput[i+1] )))  // letter followed by =^_
        {
            myinput.insert(i+1," ");
        }
    }
  //  std::cout << "Adjusted myinput " << myinput << std::endl;

    std::vector<std::string> mytokens = split(myinput, ' ');

    // now parse the objects
    std::vector<int16_t> returnvalue; returnvalue.resize(0);
    int waslastapitch = 0;

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

                if (mytokens[i][0]=='^')
                {
                    relpitch = 1;
                    mytokens[i].erase(0,1);
                }
                if (mytokens[i][0]=='_')
                {
                    relpitch = -1;
                    mytokens[i].erase(0,1);
                }
                if (mytokens[i][0]=='=')
                {
                    mytokens[i].erase(0,1);
                }


                // now we definitely have to start with a letter
                if ( mytokens[i][0] == 'C' ) relpitch += 12;
                if ( mytokens[i][0] == 'D' ) relpitch += 14;
                if ( mytokens[i][0] == 'E' ) relpitch += 16;
                if ( mytokens[i][0] == 'F' ) relpitch += 17;
                if ( mytokens[i][0] == 'G' ) relpitch += 19;
                if ( mytokens[i][0] == 'A' ) relpitch += 21;
                if ( mytokens[i][0] == 'B' ) relpitch += 23;
                if ( mytokens[i][0] == 'c' ) relpitch += 24;
                if ( mytokens[i][0] == 'd' ) relpitch += 26;
                if ( mytokens[i][0] == 'e' ) relpitch += 28;
                if ( mytokens[i][0] == 'f' ) relpitch += 29;
                if ( mytokens[i][0] == 'g' ) relpitch += 31;
                if ( mytokens[i][0] == 'a' ) relpitch += 33;
                if ( mytokens[i][0] == 'b' ) relpitch += 35;
                mytokens[i].erase(0,1);

                // and finally we can only have a "," or a "'" to raise or lower it by an octave
                if ( mytokens[i].length() > 0)
                {
                    if (mytokens[i][0] == ',') {relpitch -= 12;}
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
    return returnvalue;
}



bool IsTone(std::string input)
{
    if (input.length()>0)  // any tone must have at least one character
    {
        if ((input[0] == '[') || (input[0]=='^')|| (input[0]=='_') || (input[0]=='='))  // a tone can be in brackets or with ^ _ or =
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else return false;
}

bool AlreadyIn(int myX,std::vector<int> alreadyused)
{
	bool returnvalue = false;
	for (size_t k = 0; k < alreadyused.size(); k++)
	{
		if (myX == alreadyused[k]) returnvalue = true;
	}
	return returnvalue;
}

#endif
