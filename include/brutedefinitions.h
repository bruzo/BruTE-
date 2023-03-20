#ifndef BRUTEDEFS_H
#define BRUTEDEFS_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

    const double timetoticks = 0.60476973728946;

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

    std::string lotroinstruments_formal[22] =
          {"Lute of the Ages", "Basic Harp", "Theorbo", "Horn", "Clarinet", "Flute", "Bagpipes", "Pipgorn", "Drums",
     //      0      1        2         3         4          5        6           7         8
           "Cowbell", "Moor Cowbell", "Basic Lute", "Misty M. Harp", "Student Fiddle", "Lonely M. Fiddle", "Sprightly Fiddle", "Travellers Tr.", "Bardic Fiddle",
     //      9          10                 11            12         13          14           15         16          17
           "Basic Fiddle", "Basic Basson", "Lonely M. Basson", "Brusque Basson"};
     //      18             19              20            21
//     const char * pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string pitchnames[38] = {"=C,","^C,","=D,","^D,","=E,","=F,","^F,","=G,","^G,","=A,","^A,","=B,", "=C","^C","=D","^D","=E","=F","^F","=G","^G","=A","^A","=B", "=c","^c","=d","^d","=e","=f","^f","=g","^g","=a","^a","=b","=c'", "^c'" };

     std::string volumenames[8] = {"+ppp+", "+pp+", "+p+", "+mp+", "+mf+", "+f+", "+ff+", "+fff+"};

     std::string fullvolumenames[10] = {"+pppp+", "+ppp+", "+pp+", "+p+", "+mp+", "+mf+", "+f+", "+ff+", "+fff+", "+ffff+"};



     std::vector<std::vector<float>> fullvolumegains = {
                                        {0.201 , 0.201   , 0.2963  ,  0.3647 ,  0.4608  ,   0.5507  ,    0.644  ,   0.74  ,   0.774  , 0.774},   // lute of the ages 1
                                        {0.231 , 0.231   , 0.35    ,  0.4965  ,  0.606    ,   0.709   ,    0.795  ,   0.92 ,   0.96  , 0.96},    // harp 2
                                        {0.108 , 0.108   , 0.1743   ,  0.213  ,  0.2654  ,   0.3244  ,    0.3725 ,   0.4137,   0.4416 , 0.4416},  // theorbo 3
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // horn 4
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // clarinet 5
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // flute 6
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // bagpipes 7
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // pibgorn 8
                                        {0.14, 0.14, 0.21, 0.3, 0.42, 0.5, 0.57, 0.65, 0.7, 0.7},   // drums 9
                                        {0.14, 0.14, 0.21, 0.3, 0.42, 0.5, 0.57, 0.65, 0.7, 0.7},   // cowbell 10
                                        {0.14, 0.14, 0.21, 0.3, 0.42, 0.5, 0.57, 0.65, 0.7, 0.7},   // moor bell 11
                                        {0.092, 0.092, 0.131 , 0.164 , 0.200 , 0.245 , 0.302,0.342, 0.362, 0.362},   // basic lute 12
                                        {0.231 , 0.231   , 0.35    ,  0.4965  ,  0.606    ,   0.709   ,    0.795  ,   0.92 ,   0.96  , 0.96},   // misty M harp 13
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // student fiddle 14
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // lonely M fiddle  15
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // sprightly fiddle  16
                                        {0.14, 0.14, 0.22, 0.26, 0.38, 0.51, 0.65, 0.7, 0.8, 0.8},   // travellers t 17
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // bardic  18
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // basic fiddle  19
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // basic basson  20
                                        {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},   // lonely m basson
                                        {0.2, 0.2, 0.3, 0.3, 0.5, 0.65, 0.66, 0.69, 0.77, 0.77}    // brusque basson
                                                        };

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

std::map<std::string, int> VelocityValues =
{
              {"+pppp+" , 0},
              {"+ppp+", 1},
              {"+pp+", 2},
              {"+p+", 3},
              {"+mp+", 4},
              {"+mf+", 5},
              {"+f+", 6},
              {"+ff+", 7},
              {"+fff+", 8},
              {"+ffff+", 9}
};
                                        //   pppp     ppp      pp        p       mp        mf         f         ff       fff   ffff
std::vector<float> volconversionfactors = { 1.0/7.0, 1.0/5.0, 1.0/2.8, 1.0/1.9, 1.0/1.55, 1.0/1.32, 1.0/1.165, 1.0/1.045, 1.0, 1.0/0.9727   };

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

typedef struct STEREO_WAV_HEADER {
  /* RIFF Chunk Descriptor */
  uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
  uint32_t ChunkSize;                     // RIFF Chunk Size
  uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
  /* "fmt" sub-chunk */
  uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
  uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
  uint16_t AudioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
                            // Mu-Law, 258=IBM A-Law, 259=ADPCM
  uint16_t NumOfChan = 2;   // Number of channels 1=Mono 2=Sterio
  uint32_t SamplesPerSec = 44100;   // Sampling Frequency in Hz
  uint32_t bytesPerSec = 44100 * 4; // bytes per second
  uint16_t blockAlign = 4;          // 2=16-bit mono, 4=16-bit stereo
  uint16_t bitsPerSample = 16;      // Number of bits per sample
  /* "data" sub-chunk */
  uint8_t Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
  uint32_t Subchunk2Size;                        // Sampled data length
} stereo_wav_hdr;

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

#endif
