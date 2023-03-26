#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "chord.h"

#include "brutedefinitions.h"

class ConfigFile
{
public:

   void ImportDrumMaps();
   void ImportPitchBendInstructions();
   void ImportConfigFile(char * infilename);
   void ParseConfigMapping(std::stringstream * configtext);

   std::vector< std::vector < int >  > m_drumsmapd;

   std::string m_songname;
   std::string m_transcribername;

   int m_bpm;
   int m_minstepmod;
   int m_InvertMajor;
   int m_generalpitch;
   int m_oversampling;
   int m_globalvolume;
   double m_volumecompress;

   int m_namingscheme;                              // 0: rocks, 1: TSO, 2: Meisterbarden, 3: Bara, 4 Llelle
   bool m_nopitchguessing;
   bool m_nobackfolding;
   int m_fadeoutlength;

   int m_maxchoordnotes;
   double m_dohumanization;

   bool m_dopitchbends;
   double m_pitchbendamplifier;

   // data for the abc tracks (itrack)
   std::vector < int > m_polymap;    // polyphony per itrack
   std::vector < int > m_polymapdir; //  play the high (top=0) or low (bottom=1) notes of reduced polyphones
   std::vector < int > m_instrumap;  //  instrument per itrack
   std::vector < int > m_durmap;     //  minimal note duration per itrack
   std::vector < int > m_durmaxmap;  //  maximal note duration per itrack
   std::vector < int > m_drumforcowbellmap; // changes the name in the abc for tracks with value 1 to cowbell instead of drums (for easier cowbells)

   std::vector < int > m_voladjustmap; // Map to specify if this track will be volume adjusted for current missmatch in lotro
   std::vector < int > m_invertmap;    // is this an inverted itrack?
   std::vector < int > m_mtdmap;       // list of humanizeroptions per itrack

   std::vector < int > m_panningmap;   // midi position of tracks
   std::vector < int > m_zpanningmap;
   std::vector < int > m_idmap;

   std::vector < int >m_ialternatemap;
   std::vector < int >m_ialternatepart;

   // irange and range map is splitted from old irangemap
   std::vector < int > m_irangemapl;
   std::vector < int > m_irangemaph;

   std::vector < float > m_itrillermap;
   std::vector < int > m_ipitchbendmap;  // pitchbend per itrack
   std::vector < int > m_ipitchbendmethodmap;
   std::vector < int > m_idurationsplitmap;
   std::vector < int > m_idurationsplitpartmap;

   std::vector < int > m_tmap;
   std::vector < int > m_vmap;
   std::vector < int > m_pmap;
   std::vector < float > m_dmap;
   std::vector < int > m_ipriomap;
   std::vector < int > m_imfmap;
   std::vector < int > m_imsmap;
   std::vector < int > m_itrackdivide;
   std::vector < int > m_itrackdividepart;
   std::vector < int > m_idrumstylemap;
   std::vector < int > m_idrumsingleinstrument;
   std::vector < int > m_idirectmapping;
   std::vector < int > m_itrackvoices;
   std::vector < int > m_itrackvoice;
   std::vector < int > m_ialignmap;

   std::vector < int > m_arpeggiomap;  // 0 = no arpeggio, otherwise this is arpeggio duration
   std::vector < int > m_arpeggioincmap; // increment of the arpeggio



   // data structures for the miditrack line
   std::vector < std::vector < int > > m_trackmap;  // list of miditracks per itrack
   std::vector < std::vector < int > > m_volumemap; // list of volume modification of miditracks per itrack
   std::vector < std::vector < int > > m_pitchmap;  // pitch adjustments of miditrack in itrack
   std::vector < std::vector < float > > m_delaymap;  // list of delays of miditracks in itrack
   std::vector < std::vector < int > > m_priomap;   // list of the priorities of miditracks in itrack


   std::vector < std::vector < int > > m_mfmap;     // volume modulation frequency of miditracks in itrack
   std::vector < std::vector < int > > m_msmap;     // modulation phaseshift of miditracks in itrack

   std::vector < std::vector < int > > m_splitvoicesmap; // how many voices to split for miditrack in itrack
   std::vector < std::vector < int > > m_splitvoicemap; // which one of those voices is this miditrack in this itrack ?

   std::vector < std::vector < int > > m_durationsplitmap; // which one of the voices in this miditrack are split in this itrack
   std::vector < std::vector < int > > m_durationsplitpartmap; // which one of the voices in this miditrack are split in this itrack

   std::vector < std::vector<int> > m_drumstylemap; // drum style per miditrack in itrack
   std::vector < std::vector<int> > m_drumsingleinstrument; // pick just this midi drum per miditrack in itrack
   std::vector < std::vector<int> > m_directmapping;
   std::vector < std::vector<int> > m_rangemapl;    //  list of the ranges of the miditracks per itrack
   std::vector < std::vector<int> > m_rangemaph;    //  list of the ranges of the miditracks per itrack


   std::vector < std::vector<int> > m_trackdivide;    // divide miditrack of itrack into parts ( 0 don't, >1  )
   std::vector < std::vector<int> > m_trackdividepart; //part n of trackdivide ( eg: 1 of 2 ...)

   // this is a per miditrack per itrack record of the alternating parts
   std::vector < std::vector<int> > m_alternatemap; // is this an alternating track? (>1) how many total tracks are there?
   std::vector < std::vector<int> > m_alternatepart; // which one of the alternating tracks is this?

   // this is per miditrack per itrack record of tone alignment
   std::vector < std::vector<int> > m_alignmap;    // list of close range alignments per itrack

   // triller per miditrack of itrack
   std::vector < std::vector<float> > m_trillermap;

   // pitchbendquantization per miditrack of itrack
   std::vector < std::vector<int> > m_pitchbendmap;
   std::vector < std::vector<int> > m_pitchbendmethodmap;

   float m_DATA_maxdelay;

   std::vector< int > abctrackpositions_x;
   std::vector< int > abctrackpositions_y;

private:

    // Singular variables
    int m_minstrument;
    int m_mpitch;
    int m_mvol;
    int m_mpoly;
    int m_mpolyd;
    int m_mdivide;
    int m_mdur;
    int m_maxdur;
    float m_mdelay;
    int m_mprio;
    int m_mff;
    int m_msm;
    int m_drumstyle;
    int m_drumforcowbell;
    int m_voladjust;
    int m_panning;
    int m_zpanning;
    int m_id;
    int m_in_midi_drum;
    int m_direct;
    int m_malign;
    int m_alternatecount;
    int m_alternatepartnumber;
    int m_defaultrange[2];
    int m_arpeggioduration;
    int m_mtd;

    int m_go_on_parts;
    float m_trillerfreq;
    int m_pitchbendfreq;
    int m_pitchbendmethod;
    int m_invertthis;
    int m_arpeggioinc;
    int m_idurationsplit;
    int m_idurationsplitpart;
    int m_idurationpart;
    int m_ivoice;
    int m_ivoices;
    int m_ialign;

};


void ConfigFile::ImportDrumMaps()
{
   std::ifstream drumfile;
   m_drumsmapd.resize(999);

   // set the default map

   for( int i = 0; i < 999; i++ )
   {
      drumfile.open( "drum"+std::to_string(i)+".drummap.txt" );
      if (!drumfile.fail())
      {
         m_log << "Found drum file " << i << std::endl;
         m_drumsmapd[i].resize(128);
         // default is not mapped
         for (int j =0; j < 128; j++) m_drumsmapd[i][j] = -1;


         while( !drumfile.fail() )
         {
            std::string thisline;
            std::getline(drumfile, thisline);
            std::vector< std::string > arguments = split(thisline, ' ');

            // check if this is a comment
            if (arguments.size() > 0)
            if (arguments[0].size() > 0)
            if ( arguments[0].c_str()[0] != '%')
            {
               if (arguments.size()> 2)
               {
                   int midisample = std::atoi( arguments[0].c_str() );
                   int lotrosample = std::atoi( arguments[2].c_str() ) - 36;
                   m_drumsmapd[i][midisample]=lotrosample;
                //int number = std::atoi( arguments[j].c_str() );
               }
            }
         }
      }
      else
      {  // file not found, so no mapping for this one
         m_drumsmapd[i].resize(128);
         // default is not mapped
         for (int j =0; j < 128; j++) m_drumsmapd[i][j] = -1;
      }
      drumfile.close();
   }
}

void ConfigFile::ImportPitchBendInstructions()
{
   std::ifstream pitchbendfile;
   pitchbendfile.open( "pitchbends.config" );
   m_log << "Importing pitchbends.config." << std::endl;
   if (pitchbendfile.fail())
   {
       m_log << "Could not find pitchbend.config, generating default." << std::endl;
       pitchbendfile.close();
       std::ofstream newfile;
       newfile.open("pitchbends.config");
       newfile << "yes 2.0" << std::endl;
       newfile << "human 0" << std::endl;
       newfile.close();
   }
   pitchbendfile.close();
   pitchbendfile.open("pitchbends.config");
   std::vector< std::string > myline = split(readline( pitchbendfile ),' ');
   if (myline[0] == "yes")
   {
       m_dopitchbends = true;
       m_pitchbendamplifier = atof( myline[1].c_str());
       m_log << "Pitchbends are going to be processed with relative strength " << m_pitchbendamplifier << std::endl;
   }
   else
   {
       m_log << "No Pitchbend processing selected." << std::endl;
   }

   // humanization
   myline = split( readline( pitchbendfile ),' ');
   m_dohumanization = atof(myline[1].c_str());
   pitchbendfile.close();
   if (m_dohumanization > 0) m_log << "Artificial Humanization selected .. results may not be pleasing!" << std::endl;
}

void ConfigFile::ParseConfigMapping(std::stringstream * mappingtext)
{
    std::stringstream myconfigfile;
    myconfigfile << mappingtext->rdbuf();

    // this is the header of the file
    std::string songnameline;
    std::stringstream mysongname;
    std::getline(myconfigfile, songnameline);
    std::vector< std::string > songnamelinelist = split(songnameline,' ');

    abctrackpositions_x = std::vector<int>();
    abctrackpositions_y = std::vector<int>();

    for (unsigned int i = 1; i < songnamelinelist.size(); i++)
    {
        mysongname << songnamelinelist[i] << " ";
    }
    m_songname = mysongname.str();

    std::cout << "Songname: ";
    std::cout << m_songname << std::endl;
    m_log << "Songname: " << m_songname << std::endl;

    // get speed modifier
    std::string mappingtextline;
    std::getline(myconfigfile, mappingtextline);
    m_minstepmod = atoi( split( mappingtextline ,' ')[1].c_str() );

    if (m_minstepmod < -75) m_minstepmod = -75;
    if (m_minstepmod > 200) m_minstepmod = 200;

    // pitch line
    std::getline(myconfigfile, mappingtextline);
    std::vector< std::string > myline = split(mappingtextline,' ');
    m_generalpitch = 0;
    if ( myline.size() > 1 ) m_generalpitch = atoi(myline[1].c_str());
    // we read this only for historic reasons and will just ignore it now
    m_oversampling = 2;
    // if ( myline.size() > 2 ) m_oversampling = atoi(myline[3].c_str());
    // tonality change option
    m_InvertMajor = 0;
    if ( myline.size() > 4 ) m_InvertMajor = atoi(myline[4].c_str());

    // conversion style
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline,' ');
    m_namingscheme = 0; // default is rocks
    if ( myline.size() > 1 ) if ( myline[1] == "TSO" ) m_namingscheme = 1;
    if ( myline.size() > 1 ) if ( myline[1] == "Meisterbarden" ) m_namingscheme = 2;
    if ( myline.size() > 1 ) if ( myline[1] == "Bara" ) m_namingscheme = 3;
    if ( myline.size() > 1 ) if ( myline[1] == "Llelle" ) m_namingscheme = 4;

    // globalvolume
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline,' ');
    m_globalvolume = 0;
    if (myline.size() > 1 ) m_globalvolume = atoi(myline[1].c_str());

    // global volume compression
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline,' ');
    m_volumecompress = 1.0;
    if (myline.size() > 1 ) m_volumecompress = atof(myline[1].c_str());

    m_nopitchguessing = false;
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline, ' ');
    if ( myline[0].c_str()[0] == 'n' ) m_nopitchguessing = true;

    m_nobackfolding = false;
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline, ' ');
    if ( myline[0].c_str()[0] == 'n' ) m_nobackfolding = true;

    m_fadeoutlength = 0;
    std::getline(myconfigfile, mappingtextline);
    myline = split(mappingtextline, ' ');
    if ( myline.size() > 2 ) m_fadeoutlength = atoi(myline[2].c_str());
    m_fadeoutlength = static_cast<int> (  m_fadeoutlength * 125 * 16 / 60 );

    // Transcribername
    std::string tnameline;
    std::stringstream mytname;
    std::getline(myconfigfile, tnameline);
    std::vector< std::string > tnamelinelist = split(tnameline,' ');
    for (unsigned int i = 1; i < tnamelinelist.size(); i++)
    {
        mytname << tnamelinelist[i] << " ";
    }
    m_transcribername = mytname.str();

    std::cout << "Transcriber: ";
    std::cout << m_transcribername << std::endl;
    m_log << "Transcriber: " << m_transcribername << std::endl;

    // initialize all of the vectors and variables
    m_trackmap.resize(0); //  list of miditracks per itrack
    m_volumemap.resize(0);//  list of volumechanges of the miditracks per itrack
    m_pitchmap.resize(0); //  list of pitches       of the miditracks per itrack
    m_delaymap.resize(0); //  list of the delays    of the miditracks per itrack
    m_priomap.resize(0);  //  list of the priorities of the miditracks per itrack
    m_mfmap.resize(0);    //  list of modulation frequencies of the miditracks per itrack
    m_msmap.resize(0);    //  list of modulation phaseshift of the miditracks per itrack
    m_splitvoicesmap.resize(0); // into how many voices should this miditrack in this itrack be splitted
    m_splitvoicemap.resize(0);  // which one of those voices is this miditrack in this itrack ?

    m_durationsplitmap.resize(0);  // which one of the voices in this miditrack are split in this itrack
    m_durationsplitpartmap.resize(0);

    m_polymap.resize(0);        //  polyphony per itrack
    m_polymapdir.resize(0);     //  play the high (top) or low (bottom) notes of reduced polyphones
    m_trackdivide.resize(0);    //  divide track into parts ( 0 don't, >1  )
    m_trackdividepart.resize(0);//  part n of trackdivide ( eg: 1 of 2 ...)
    m_instrumap.resize(0);      //  instrument per itrack
    m_durmap.resize(0);         //   minimal note duration per itrack
    m_durmaxmap.resize(0);      //   maximal note duration per itrack
    m_drumstylemap.resize(0);   //   drum style per miditrack in itrack
    m_drumsingleinstrument.resize(0);// pick just this midi drum per miditrack in itrack
    m_directmapping.resize(0); // for direct mapping
    m_drumforcowbellmap.resize(0);// changes the name in the abc for tracks with value 1 to cowbell instead of drums (for easier cowbells)
    m_voladjustmap.resize(0);   //   Map to specify if this track will be U15.3 volume adjusted
    m_invertmap.resize(0);      // is this an inverted itrack?
    m_rangemapl.resize(0);       // list of the ranges of the miditracks per itrack
    m_rangemaph.resize(0);       // list of the ranges of the miditracks per itrack

    m_arpeggiomap.resize(0);    // list of arpeggio durations ( 0 = no arpeggio )
    m_arpeggioincmap.resize(0); // increment for arpeggio ( any integer )
    m_mtdmap.resize(0);         // list of humanizeroptions per itrack

    // this is a per miditrack per itrack record of the alternating parts
    m_alternatemap.resize(0); // is this an alternating track? (>1) how many total tracks are there?
    m_alternatepart.resize(0);// which one of the alternating tracks is this?

    // this is per miditrack per itrack record of tone alignment
    m_alignmap.resize(0);     // list of close range alignments per itrack

    // triller
    m_trillermap.resize(0);

    // pitchbends
    m_pitchbendmap.resize(0);
    m_pitchbendmethodmap.resize(0);

    // pannings map
    m_panningmap.resize(0);
    m_zpanningmap.resize(0);
    m_idmap.resize(0);


    // singular variables to default

    m_minstrument = 0;
    m_mpitch = 0;
    m_mvol = 0;
    m_mpoly = 0;
    m_mdivide = 0;
    m_mdur = 1;
    m_mdelay = 0;
    m_mprio = 1;
    m_mff = 0;
    m_msm = 0 ;
    m_drumstyle = 0;
    m_drumforcowbell = 0;
    m_voladjust = 0;
    m_panning = 64;
    m_zpanning = 0;
    m_id = 0;
    m_in_midi_drum = 0;
    m_direct = -1;
    m_malign = 0; // default is no align

    m_alternatecount = 1;
    m_alternatepartnumber = 1;
    m_defaultrange[0] = 0; m_defaultrange[1] =36;
    m_arpeggioduration = 0;
    m_mtd = 0; // default humanization is 0

    m_DATA_maxdelay = 0;

    std::vector< std::string > thisline;
    while (!myconfigfile.fail())
    {
       // read next line
       std::getline(myconfigfile, mappingtextline);
       thisline = split(mappingtextline,' ');

       // skip over excluded part
       if (thisline.size() > 0) if (thisline[0].size() > 0) if (thisline[0][0] == '*')
       {
          int gofurther = 1;
          while( gofurther == 1)
          {
             std::getline(myconfigfile, mappingtextline);
             thisline = split(mappingtextline,' ');
             if (myconfigfile.fail()) gofurther = 0;
              if (thisline.size() > 0) if (thisline[0].size() > 0) if (thisline[0][0] == '*')
                {gofurther = 0;}
          }
       }
// check for the abctrack positioning
if (thisline.size() > 0)
{
    if (thisline[0].size() > 1)
        if ((thisline[0][0] == '%' ) && (thisline[0][1] == 'B'))
        {
            // this line has some info
            abctrackpositions_x.push_back( atoi(thisline[3].c_str()));
            abctrackpositions_y.push_back( atoi(thisline[5].c_str()));
        }
}

// we can do nothing if this line is empty
if (thisline.size() > 0)
{
   // don't do anything if line starts with % or is empty
   if (thisline[0].size() > 0)
      if ( thisline[0][0] != '%' )
      {
         // now we have a line with something in it, no comment etc

         // check for abctrack begin
         if (thisline[0] == "abctrack"){
            if (thisline[1] == "begin")
         {
             // std::cout << "this is the start of an abc track " << std::endl;
             m_minstrument = 0;
             m_mpoly  = m_maxchoordnotes;
             m_mpolyd = 1;   // top tones removed first
             m_mdur   = 1;   // minimal quantized duration
             m_maxdur = 10000; // maximal default duration, not to interfere with other value
             m_drumstyle = 0;
             m_alternatecount = 1;
             m_alternatepartnumber = 1;
             m_defaultrange[0] = 0; m_defaultrange[1] = 36;

             m_trillerfreq = 0;
             m_pitchbendfreq = 0;
             m_pitchbendmethod = 0;
             m_voladjust = 0;
             m_panning = 64;
             m_zpanning = 0;
             m_id = 0;
             m_drumforcowbell = 0;
             m_in_midi_drum = 0;
             m_direct = -1;
             m_invertthis = 0; // default is not to invert
             m_arpeggioduration = 0;
             m_arpeggioinc = 1;
             m_mtd = 0;

             m_idurationsplit = 0; // default is not to split
             m_idurationsplitpart = 0; // default is first part
             m_idurationpart = 0; // first part

             m_ivoice = 0;  // default is first voice
             m_ivoices = 0; // default is split into 0 track (don't split)

             m_ialign = 0; // default is no shifting in time, value is in miditicks +/- to align to estimated most probable beat

             // vectors
             m_ialternatemap.resize(0);
             m_ialternatepart.resize(0);
             m_irangemapl.resize(0);
             m_irangemaph.resize(0);
             m_itrillermap.resize(0);
             m_ipitchbendmap.resize(0);
             m_ipitchbendmethodmap.resize(0);
             m_idurationsplitmap.resize(0);
             m_idurationsplitpartmap.resize(0);
             m_tmap.resize(0);
             m_vmap.resize(0);
             m_pmap.resize(0);
             m_dmap.resize(0);
             m_ipriomap.resize(0);
             m_imfmap.resize(0);
             m_imsmap.resize(0);
             m_itrackdivide.resize(0);
             m_itrackdividepart.resize(0);
             m_idrumstylemap.resize(0);
             m_idrumsingleinstrument.resize(0);
             m_idirectmapping.resize(0);
             m_itrackvoices.resize(0);
             m_itrackvoice.resize(0);
             m_ialignmap.resize(0);
         }
            if (thisline[1] == "end")
         {
             //std::cout << "this is the end of an abc track " << std::endl;
             m_trackmap = AppendIU(m_trackmap, m_tmap);
             m_volumemap = AppendIU(m_volumemap, m_vmap);
             m_pitchmap = AppendIU(m_pitchmap, m_pmap);
             m_delaymap = AppendFU(m_delaymap, m_dmap);
             m_priomap  = AppendIU(m_priomap, m_ipriomap);
             m_mfmap = AppendIU(m_mfmap, m_imfmap);
             m_msmap = AppendIU(m_msmap, m_imsmap);
             m_rangemapl = AppendIU(m_rangemapl, m_irangemapl);
             m_rangemaph = AppendIU(m_rangemaph, m_irangemaph);
             m_trackdivide = AppendIU(m_trackdivide, m_itrackdivide);
             m_trackdividepart = AppendIU(m_trackdividepart, m_itrackdividepart);
             m_drumstylemap = AppendIU(m_drumstylemap, m_idrumstylemap);
             m_drumsingleinstrument = AppendIU(m_drumsingleinstrument, m_idrumsingleinstrument);
             m_directmapping = AppendIU(m_directmapping, m_idirectmapping);
             m_splitvoicesmap = AppendIU(m_splitvoicesmap, m_itrackvoices);
             m_splitvoicemap = AppendIU(m_splitvoicemap, m_itrackvoice);
             m_alternatemap = AppendIU(m_alternatemap, m_ialternatemap);
             m_alternatepart = AppendIU(m_alternatepart, m_ialternatepart);
             m_trillermap = AppendFU(m_trillermap, m_itrillermap);
             m_pitchbendmap = AppendIU(m_pitchbendmap, m_ipitchbendmap);
             m_pitchbendmethodmap = AppendIU(m_pitchbendmethodmap, m_ipitchbendmethodmap);
             m_polymap = AppendI(m_polymap, m_mpoly);
             m_instrumap = AppendI(m_instrumap, m_minstrument);
             m_polymapdir = AppendI(m_polymapdir, m_mpolyd);
             m_durmap = AppendI(m_durmap, m_mdur);
             m_durmaxmap = AppendI(m_durmaxmap ,m_maxdur);
             m_panningmap = AppendI(m_panningmap, m_panning);
             m_zpanningmap = AppendI(m_zpanningmap, m_zpanning);
             m_idmap = AppendI(m_idmap, m_id );
             m_drumforcowbellmap = AppendI(m_drumforcowbellmap, m_drumforcowbell);
             m_arpeggiomap = AppendI(m_arpeggiomap, m_arpeggioduration);
             m_arpeggioincmap = AppendI(m_arpeggioincmap, m_arpeggioinc);
             m_invertmap = AppendI(m_invertmap, m_invertthis);
             m_voladjustmap = AppendI(m_voladjustmap, m_voladjust);
             m_durationsplitmap=AppendIU(m_durationsplitmap, m_idurationsplitmap);
             m_durationsplitpartmap=AppendIU(m_durationsplitpartmap, m_idurationsplitpartmap);
             m_alignmap  =AppendIU(m_alignmap, m_ialignmap);
             m_mtdmap    =AppendI(m_mtdmap, m_mtd);

         }

         }
         if (thisline[0] == "polyphony"){
             m_mpoly = atoi(thisline[1].c_str());
             if (thisline[2] == "top") m_mpolyd = 1;
             if (thisline[2] == "bottom") m_mpolyd = 0;
         }
         if (thisline[0] == "instrument")  // instrument <name> <drumstyle> <c/insample> <outsample?>
         {
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments[j])
                m_minstrument = j;
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments2[j])
                m_minstrument = j;
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments3[j])
                m_minstrument = j;

             if ( thisline.size() > 2 ){
                if (m_minstrument == 8) m_drumstyle = atoi(thisline[2].c_str());
             }
             if ( thisline.size() > 3 )
             {


                if (m_minstrument ==8)
                {
                   if ( thisline[3] == "c" ) { m_drumforcowbell = 1; }
                   else {
                      m_in_midi_drum = atoi(thisline[3].c_str());
                   }
                }
                else{
                   if ( thisline.size() > 4 )
                   {
                       if ( thisline[2]=="d")
                       {
                          m_direct = atoi(thisline[4].c_str());
                          m_in_midi_drum = atoi(thisline[3].c_str());
                       }
                   }
                }
             }
         }
         if (thisline[0] == "duration")
         {
             m_mdur = atoi(thisline[1].c_str());
             if (thisline.size() > 2) m_maxdur = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "split")
         {
            m_ivoices = atoi(thisline[1].c_str());
            m_ivoice  = m_ivoices;
         }
         if (thisline[0] == "durationsplit")
         {
         // this is the quantized length for the durationsplit and if this is the first or the second half
         // durationsplit 6 0 would be everything <6 is part 0, >= 6 part 1
            m_idurationsplit = atoi(thisline[1].c_str());
            m_idurationpart  = atoi(thisline[2].c_str());
         }
         if (thisline[0] == "alternate")
         {
            m_alternatecount = atoi(thisline[1].c_str());
            m_alternatepartnumber = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "triller")
         {
            m_trillerfreq = atof(thisline[1].c_str());
            // if (m_trillerfreq == 1) m_trillerfreq = 2;  // the user should know what he does!
         }

         if (thisline[0] == "pitchbendinfo")
         {
             m_pitchbendfreq = atoi(thisline[1].c_str());
             m_pitchbendmethod = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "panning")
         {
            m_panning = atoi(thisline[1].c_str());
            if (thisline.size() > 2)
            {
               m_zpanning = atoi(thisline[2].c_str());
               m_id = atoi(thisline[3].c_str());
            }
            //if (m_panning < 0) m_panning = 0;
            //if (m_panning > 127) m_panning = 127;
         }

         if (thisline[0] == "miditrack")
         {
             m_tmap = AppendI(m_tmap, atoi(thisline[1].c_str()));
             m_pmap = AppendI(m_pmap, atoi(thisline[3].c_str()));
             m_vmap = AppendI(m_vmap, atoi(thisline[5].c_str()));

             m_irangemapl = AppendI(m_irangemapl, m_defaultrange[0]);
             m_irangemaph = AppendI(m_irangemaph, m_defaultrange[1]);
             m_defaultrange[0] = 0; m_defaultrange[1]=36;
         }

         if (thisline[0] == "arpeggio")
         {
             m_arpeggioduration = atoi( thisline[1].c_str() );
             if (m_arpeggioduration == 1) m_arpeggioduration = 2;
             if (thisline.size() > 2) m_arpeggioinc = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "directmapping")
         {
             m_in_midi_drum = atoi( thisline[1].c_str());
             m_direct = atoi( thisline[2].c_str());
         }

         if (thisline[0] == "miditrack")
         {
             m_itrackvoices = AppendI(m_itrackvoices, m_ivoices);
             m_itrackvoice = AppendI(m_itrackvoice, m_ivoice);
             m_ialternatemap = AppendI(m_ialternatemap, m_alternatecount);
             m_ialternatepart = AppendI(m_ialternatepart, m_alternatepartnumber);
             m_idurationsplitmap = AppendI(m_idurationsplitmap, m_idurationsplit);
             m_idurationsplitpartmap = AppendI(m_idurationsplitpartmap, m_idurationpart);

             m_idrumstylemap = AppendI(m_idrumstylemap, m_drumstyle);
             m_idrumsingleinstrument = AppendI(m_idrumsingleinstrument,m_in_midi_drum);
             m_idirectmapping = AppendI(m_idirectmapping, m_direct);


             m_itrillermap = AppendF(m_itrillermap, m_trillerfreq);
             m_ipitchbendmap = AppendI(m_ipitchbendmap, m_pitchbendfreq);
             m_ipitchbendmethodmap = AppendI(m_ipitchbendmethodmap, m_pitchbendmethod);
             m_ialignmap = AppendI(m_ialignmap, m_ialign);

             // after all this has been added we set the default per miditrack again
             m_idurationsplit = 0;
             m_idurationpart = 0;
             m_ialign = 0;
             m_ivoices= 0;
             m_ivoice = 0;
             m_alternatecount = 1;
             m_alternatepartnumber = 1;
             m_trillerfreq = 0;
             m_pitchbendfreq = 0;
             m_pitchbendmethod = 0;

             if (thisline.size() > 6)
             {
                 m_dmap = AppendF(m_dmap, atof(thisline[7].c_str()));
                 if (atof(thisline[7].c_str()) > m_DATA_maxdelay) m_DATA_maxdelay = atof(thisline[7].c_str());
             }
             else
             {
                 m_dmap = AppendF(m_dmap, 0);
             }

             if (thisline.size() > 8)
             {
                 m_ipriomap = AppendI( m_ipriomap, atoi(thisline[9].c_str()));
             }
             else
             {
                 m_ipriomap = AppendI( m_ipriomap, 1);
             }

             if (thisline.size() > 11)
             {
                m_itrackdivide = AppendI(m_itrackdivide, atoi(thisline[11].c_str()));
                m_itrackdividepart = AppendI(m_itrackdividepart, atoi(thisline[12].c_str()));
             }
             else
             {
                m_itrackdivide = AppendI(m_itrackdivide, 1);
                m_itrackdividepart = AppendI(m_itrackdividepart, 0);
             }

             if (thisline.size() > 11)
             {
                 m_itrackdivide = AppendI(m_itrackdivide, atoi(thisline[11].c_str()));
                 m_itrackdividepart = AppendI(m_itrackdividepart, atoi(thisline[12].c_str()));
             }
             else
             {
                 m_itrackdivide = AppendI(m_itrackdivide, 1);
                 m_itrackdividepart = AppendI(m_itrackdividepart, 0);
             }
             if (thisline.size() > 15)
             {
                 m_imfmap = AppendI(m_imfmap, atoi(thisline[14].c_str()));
                 m_imsmap = AppendI(m_imsmap, atoi(thisline[15].c_str()));
             }
             else
             {
                 m_imfmap = AppendI(m_imfmap, 0);
                 m_imsmap = AppendI(m_imsmap, 0);
             }
         }
         if (thisline[0] == "voladjust")
         {
             m_voladjust = 1;
         }
         if (thisline[0] == "range")
         {
             m_defaultrange[0] = atoi(thisline[1].c_str());
             m_defaultrange[1] = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "align")
         {
             m_ialign = atoi(thisline[1].c_str());
         }

         if (thisline[0] == "invert")
         {
             m_invertthis = 1;
         }
         if (thisline[0] == "humanizer")
         {
             m_mtd = atoi(thisline[1].c_str());
         }
      }
}
   }
   m_log << "Mapping Parsed." << std::endl;
}

void ConfigFile::ImportConfigFile(char * infilename)
{
   // check for defaults file
   std::ifstream myconfigfile;
   m_bpm = 125;
   m_maxchoordnotes = 6;
   m_log << "Opening Mapping File: " << infilename << std::endl;

   myconfigfile.open(infilename);

   if (myconfigfile.fail())
   {
      // this should actually not happen .. only if remap is done before midival
      std::cout << "Could not open " << infilename << std::endl;
      m_log << "Could not open " << infilename << std::endl;
   }

   // this is the header of the file
    std::string songnameline;
    std::stringstream mysongname;
    std::getline(myconfigfile, songnameline);
    std::vector< std::string > songnamelinelist = split(songnameline,' ');
    for (unsigned int i = 1; i < songnamelinelist.size(); i++)
    {
        mysongname << songnamelinelist[i] << " ";
    }
    m_songname = mysongname.str();

    std::cout << "Songname: ";
    std::cout << m_songname << std::endl;
    m_log << "Songname: " << m_songname << std::endl;

    // get speed modifier
    m_minstepmod = atoi(split(readline( myconfigfile ),' ')[1].c_str());
    if (m_minstepmod < -75) m_minstepmod = -75;
    if (m_minstepmod > 200) m_minstepmod = 200;

    // pitch line
    std::vector< std::string > myline = split(readline( myconfigfile ),' ');
    m_generalpitch = 0;
    if ( myline.size() > 1 ) m_generalpitch = atoi(myline[1].c_str());
    // we read this only for historic reasons and will just ignore it now
    m_oversampling = 2;
    // if ( myline.size() > 2 ) m_oversampling = atoi(myline[3].c_str());
    // tonality change option
    m_InvertMajor = 0;
    if ( myline.size() > 4 ) m_InvertMajor = atoi(myline[4].c_str());

    // conversion style
    myline = split(readline( myconfigfile ),' ');
    m_namingscheme = 0; // default is rocks
    if ( myline.size() > 1 ) if ( myline[1] == "TSO" ) m_namingscheme = 1;
    if ( myline.size() > 1 ) if ( myline[1] == "Meisterbarden" ) m_namingscheme = 2;
    if ( myline.size() > 1 ) if ( myline[1] == "Bara" ) m_namingscheme = 3;
    if ( myline.size() > 1 ) if ( myline[1] == "Llelle" ) m_namingscheme = 4;

    // globalvolume
    myline = split(readline( myconfigfile ),' ');
    m_globalvolume = 0;
    if (myline.size() > 1 ) m_globalvolume = atoi(myline[1].c_str());

    // global volume compression
    myline = split(readline( myconfigfile ),' ');
    m_volumecompress = 1.0;
    if (myline.size() > 1 ) m_volumecompress = atof(myline[1].c_str());

    m_nopitchguessing = false;
    myline = split(readline(myconfigfile), ' ');
    if ( myline[0].c_str()[0] == 'n' ) m_nopitchguessing = true;

    m_nobackfolding = false;
    myline = split(readline(myconfigfile), ' ');
    if ( myline[0].c_str()[0] == 'n' ) m_nobackfolding = true;

    m_fadeoutlength = 0;
    myline = split(readline(myconfigfile), ' ');
    if ( myline.size() > 2 ) m_fadeoutlength = atoi(myline[2].c_str());
    m_fadeoutlength = static_cast<int> (  m_fadeoutlength * 125 * 16 / 60 );

    // Transcribername
    std::string tnameline;
    std::stringstream mytname;
    std::getline(myconfigfile, tnameline);
    std::vector< std::string > tnamelinelist = split(tnameline,' ');
    for (unsigned int i = 1; i < tnamelinelist.size(); i++)
    {
        mytname << tnamelinelist[i] << " ";
    }
    m_transcribername = mytname.str();

    std::cout << "Transcriber: ";
    std::cout << m_transcribername << std::endl;
    m_log << "Transcriber: " << m_transcribername << std::endl;

    // initialize all of the vectors and variables
    m_trackmap.resize(0); //  list of miditracks per itrack
    m_volumemap.resize(0);//  list of volumechanges of the miditracks per itrack
    m_pitchmap.resize(0); //  list of pitches       of the miditracks per itrack
    m_delaymap.resize(0); //  list of the delays    of the miditracks per itrack
    m_priomap.resize(0);  //  list of the priorities of the miditracks per itrack
    m_mfmap.resize(0);    //  list of modulation frequencies of the miditracks per itrack
    m_msmap.resize(0);    //  list of modulation phaseshift of the miditracks per itrack
    m_splitvoicesmap.resize(0); // into how many voices should this miditrack in this itrack be splitted
    m_splitvoicemap.resize(0);  // which one of those voices is this miditrack in this itrack ?

    m_durationsplitmap.resize(0);  // which one of the voices in this miditrack are split in this itrack
    m_durationsplitpartmap.resize(0);

    m_polymap.resize(0);        //  polyphony per itrack
    m_polymapdir.resize(0);     //  play the high (top) or low (bottom) notes of reduced polyphones
    m_trackdivide.resize(0);    //  divide track into parts ( 0 don't, >1  )
    m_trackdividepart.resize(0);//  part n of trackdivide ( eg: 1 of 2 ...)
    m_instrumap.resize(0);      //  instrument per itrack
    m_durmap.resize(0);         //   minimal note duration per itrack
    m_durmaxmap.resize(0);      //   maximal note duration per itrack
    m_drumstylemap.resize(0);   //   drum style per miditrack in itrack
    m_drumsingleinstrument.resize(0);// pick just this midi drum per miditrack in itrack
    m_directmapping.resize(0);
    m_drumforcowbellmap.resize(0);// changes the name in the abc for tracks with value 1 to cowbell instead of drums (for easier cowbells)
    m_voladjustmap.resize(0);   //   Map to specify if this track will be U15.3 volume adjusted
    m_invertmap.resize(0);      // is this an inverted itrack?
    m_rangemapl.resize(0);       // list of the ranges of the miditracks per itrack
    m_rangemaph.resize(0);       // list of the ranges of the miditracks per itrack

    m_arpeggiomap.resize(0);    // list of arpeggio durations ( 0 = no arpeggio )
    m_arpeggioincmap.resize(0); // increment for arpeggio ( any integer )
    m_mtdmap.resize(0);         // list of humanizeroptions per itrack

    // this is a per miditrack per itrack record of the alternating parts
    m_alternatemap.resize(0); // is this an alternating track? (>1) how many total tracks are there?
    m_alternatepart.resize(0);// which one of the alternating tracks is this?

    // this is per miditrack per itrack record of tone alignment
    m_alignmap.resize(0);     // list of close range alignments per itrack

    // triller
    m_trillermap.resize(0);

    // pitchbends
    m_pitchbendmap.resize(0);
    m_pitchbendmethodmap.resize(0);

    // pannings map
    m_panningmap.resize(0);


    // singular variables to default

    m_minstrument = 0;
    m_mpitch = 0;
    m_mvol = 0;
    m_mpoly = 0;
    m_mdivide = 0;
    m_mdur = 1;
    m_mdelay = 0;
    m_mprio = 1;
    m_mff = 0;
    m_msm = 0 ;
    m_drumstyle = 0;
    m_drumforcowbell = 0;
    m_voladjust = 0;
    m_panning = 64;
    m_in_midi_drum = 0;
    m_direct = -1;
    m_malign = 0; // default is no align

    m_alternatecount = 1;
    m_alternatepartnumber = 1;
    m_defaultrange[0] = 0; m_defaultrange[1] =36;
    m_arpeggioduration = 0;
    m_mtd = 0; // default humanization is 0

    m_DATA_maxdelay = 0;

    std::vector< std::string > thisline;
    while (!myconfigfile.fail())
    {
       // read next line
       thisline = split(readline( myconfigfile ),' ');

       // skip over excluded part
       if (thisline.size() > 0) if (thisline[0].size() > 0) if (thisline[0][0] == '*')
       {
          int gofurther = 1;
          while( gofurther == 1)
          {
             thisline = split(readline( myconfigfile ),' ');
             if (myconfigfile.fail()) gofurther = 0;
              if (thisline.size() > 0) if (thisline[0].size() > 0) if (thisline[0][0] == '*')
                {gofurther = 0;}
          }
       }

// we can do nothing if this line is empty
if (thisline.size() > 0)
{
   // don't do anything if line starts with % or is empty
   if (thisline[0].size() > 0)
      if ( thisline[0][0] != '%' )
      {
         // now we have a line with something in it, no comment etc

         // check for abctrack begin
         if (thisline[0] == "abctrack"){
            if (thisline[1] == "begin")
         {
             // std::cout << "this is the start of an abc track " << std::endl;
             m_minstrument = 0;
             m_mpoly  = m_maxchoordnotes;
             m_mpolyd = 1;   // top tones removed first
             m_mdur   = 1;   // minimal quantized duration
             m_maxdur = 10000; // maximal default duration, not to interfere with other value
             m_drumstyle = 0;
             m_alternatecount = 1;
             m_alternatepartnumber = 1;
             m_defaultrange[0] = 0; m_defaultrange[1] = 36;

             m_trillerfreq = 0;
             m_pitchbendfreq = 0;
             m_pitchbendmethod = 0;
             m_voladjust = 0;
             m_panning = 64;
             m_drumforcowbell = 0;
             m_in_midi_drum = 0;
             m_direct = -1;
             m_invertthis = 0; // default is not to invert
             m_arpeggioduration = 0;
             m_arpeggioinc = 1;
             m_mtd = 0;

             m_idurationsplit = 0; // default is not to split
             m_idurationsplitpart = 0; // default is first part
             m_idurationpart = 0; // first part

             m_ivoice = 0;  // default is first voice
             m_ivoices = 0; // default is split into 0 track (don't split)

             m_ialign = 0; // default is no shifting in time, value is in miditicks +/- to align to estimated most probable beat

             // vectors
             m_ialternatemap.resize(0);
             m_ialternatepart.resize(0);
             m_irangemapl.resize(0);
             m_irangemaph.resize(0);
             m_itrillermap.resize(0);
             m_ipitchbendmap.resize(0);
             m_ipitchbendmethodmap.resize(0);
             m_idurationsplitmap.resize(0);
             m_idurationsplitpartmap.resize(0);
             m_tmap.resize(0);
             m_vmap.resize(0);
             m_pmap.resize(0);
             m_dmap.resize(0);
             m_ipriomap.resize(0);
             m_imfmap.resize(0);
             m_imsmap.resize(0);
             m_itrackdivide.resize(0);
             m_itrackdividepart.resize(0);
             m_idrumstylemap.resize(0);
             m_idrumsingleinstrument.resize(0);
             m_idirectmapping.resize(0);
             m_itrackvoices.resize(0);
             m_itrackvoice.resize(0);
             m_ialignmap.resize(0);
         }
            if (thisline[1] == "end")
         {
             //std::cout << "this is the end of an abc track " << std::endl;
             m_trackmap = AppendIU(m_trackmap, m_tmap);
             m_volumemap = AppendIU(m_volumemap, m_vmap);
             m_pitchmap = AppendIU(m_pitchmap, m_pmap);
             m_delaymap = AppendFU(m_delaymap, m_dmap);
             m_priomap  = AppendIU(m_priomap, m_ipriomap);
             m_mfmap = AppendIU(m_mfmap, m_imfmap);
             m_msmap = AppendIU(m_msmap, m_imsmap);
             m_rangemapl = AppendIU(m_rangemapl, m_irangemapl);
             m_rangemaph = AppendIU(m_rangemaph, m_irangemaph);
             m_trackdivide = AppendIU(m_trackdivide, m_itrackdivide);
             m_trackdividepart = AppendIU(m_trackdividepart, m_itrackdividepart);
             m_drumstylemap = AppendIU(m_drumstylemap, m_idrumstylemap);
             m_drumsingleinstrument = AppendIU(m_drumsingleinstrument, m_idrumsingleinstrument);
             m_directmapping = AppendIU(m_directmapping, m_idirectmapping);
             m_splitvoicesmap = AppendIU(m_splitvoicesmap, m_itrackvoices);
             m_splitvoicemap = AppendIU(m_splitvoicemap, m_itrackvoice);
             m_alternatemap = AppendIU(m_alternatemap, m_ialternatemap);
             m_alternatepart = AppendIU(m_alternatepart, m_ialternatepart);
             m_trillermap = AppendFU(m_trillermap, m_itrillermap);
             m_pitchbendmap = AppendIU(m_pitchbendmap, m_ipitchbendmap);
             m_pitchbendmethodmap = AppendIU(m_pitchbendmethodmap, m_ipitchbendmethodmap);
             m_polymap = AppendI(m_polymap, m_mpoly);
             m_instrumap = AppendI(m_instrumap, m_minstrument);
             m_polymapdir = AppendI(m_polymapdir, m_mpolyd);
             m_durmap = AppendI(m_durmap, m_mdur);
             m_durmaxmap = AppendI(m_durmaxmap ,m_maxdur);
             m_panningmap = AppendI(m_panningmap, m_panning);
             m_drumforcowbellmap = AppendI(m_drumforcowbellmap, m_drumforcowbell);
             m_arpeggiomap = AppendI(m_arpeggiomap, m_arpeggioduration);
             m_arpeggioincmap = AppendI(m_arpeggioincmap, m_arpeggioinc);
             m_invertmap = AppendI(m_invertmap, m_invertthis);
             m_voladjustmap = AppendI(m_voladjustmap, m_voladjust);
             m_durationsplitmap=AppendIU(m_durationsplitmap, m_idurationsplitmap);
             m_durationsplitpartmap=AppendIU(m_durationsplitpartmap, m_idurationsplitpartmap);
             m_alignmap  =AppendIU(m_alignmap, m_ialignmap);
             m_mtdmap    =AppendI(m_mtdmap, m_mtd);

         }

         }
         if (thisline[0] == "polyphony"){
             m_mpoly = atoi(thisline[1].c_str());
             if (thisline[2] == "top") m_mpolyd = 1;
             if (thisline[2] == "bottom") m_mpolyd = 0;
         }
         if (thisline[0] == "instrument")
         {
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments[j])
                m_minstrument = j;
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments2[j])
                m_minstrument = j;
             for (int j = 0; j < nInstruments; j++) if ( thisline[1] == lotroinstruments3[j])
                m_minstrument = j;

             if ( thisline.size() > 2 )
             {
                if (m_minstrument == 8) m_drumstyle = atoi(thisline[2].c_str());
             }
             if ( thisline.size() > 3 )
             {
                if (m_minstrument ==8)
                {
                   if ( thisline[3] == "c" ) { m_drumforcowbell = 1; }
                   else {
                      m_in_midi_drum = atoi(thisline[3].c_str());
                   }
                }
                else{
                   if ( thisline.size() > 4 )
                   {
                       if ( thisline[2]=="d")
                       {
                          m_direct = atoi(thisline[4].c_str());
                          m_in_midi_drum = atoi(thisline[3].c_str());
                       }
                   }
                }
             }
         }
         if (thisline[0] == "duration")
         {
             m_mdur = atoi(thisline[1].c_str());
             if (thisline.size() > 2) m_maxdur = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "split")
         {
            m_ivoices = atoi(thisline[1].c_str());
            m_ivoice  = m_ivoices;
         }
         if (thisline[0] == "durationsplit")
         {
         // this is the quantized length for the durationsplit and if this is the first or the second half
         // durationsplit 6 0 would be everything <6 is part 0, >= 6 part 1
            m_idurationsplit = atoi(thisline[1].c_str());
            m_idurationpart  = atoi(thisline[2].c_str());
         }
         if (thisline[0] == "alternate")
         {
            m_alternatecount = atoi(thisline[1].c_str());
            m_alternatepartnumber = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "triller")
         {
            m_trillerfreq = atof(thisline[1].c_str());
         //   if (m_trillerfreq == 1) m_trillerfreq = 2;
         }

         if (thisline[0] == "pitchbendinfo")
         {
             m_pitchbendfreq = atoi(thisline[1].c_str());
             m_pitchbendmethod = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "panning")
         {
            m_panning = atoi(thisline[1].c_str());
            if (m_panning < 0) m_panning = 0;
            if (m_panning > 127) m_panning = 127;
         }

         if (thisline[0] == "miditrack")
         {
             m_tmap = AppendI(m_tmap, atoi(thisline[1].c_str()));
             m_pmap = AppendI(m_pmap, atoi(thisline[3].c_str()));
             m_vmap = AppendI(m_vmap, atoi(thisline[5].c_str()));

             m_irangemapl = AppendI(m_irangemapl, m_defaultrange[0]);
             m_irangemaph = AppendI(m_irangemaph, m_defaultrange[1]);
             m_defaultrange[0] = 0; m_defaultrange[1]=36;
         }

         if (thisline[0] == "arpeggio")
         {
             m_arpeggioduration = atoi( thisline[1].c_str() );
             if (m_arpeggioduration == 1) m_arpeggioduration = 2;
             if (thisline.size() > 2) m_arpeggioinc = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "directmapping")
         {
             m_in_midi_drum = atoi( thisline[1].c_str());
             m_direct = atoi( thisline[2].c_str());
         }


         if (thisline[0] == "miditrack")
         {
             m_itrackvoices = AppendI(m_itrackvoices, m_ivoices);
             m_itrackvoice = AppendI(m_itrackvoice, m_ivoice);
             m_ialternatemap = AppendI(m_ialternatemap, m_alternatecount);
             m_ialternatepart = AppendI(m_ialternatepart, m_alternatepartnumber);
             m_idurationsplitmap = AppendI(m_idurationsplitmap, m_idurationsplit);
             m_idurationsplitpartmap = AppendI(m_idurationsplitpartmap, m_idurationpart);

             m_idrumstylemap = AppendI(m_idrumstylemap, m_drumstyle);
             m_idrumsingleinstrument = AppendI(m_idrumsingleinstrument,m_in_midi_drum);
             m_idirectmapping = AppendI(m_idirectmapping, m_direct);


             m_itrillermap = AppendF(m_itrillermap, m_trillerfreq);
             m_ipitchbendmap = AppendI(m_ipitchbendmap, m_pitchbendfreq );
             m_ipitchbendmethodmap = AppendI(m_ipitchbendmethodmap, m_pitchbendmethod);
             m_ialignmap = AppendI(m_ialignmap, m_ialign);

             // after all this has been added we set the default per miditrack again
             m_idurationsplit = 0;
             m_idurationpart = 0;
             m_ialign = 0;
             m_ivoices= 0;
             m_ivoice = 0;
             m_alternatecount = 1;
             m_alternatepartnumber = 1;
             m_trillerfreq = 0;
             m_pitchbendfreq = 0;
             m_pitchbendmethod = 0;
             m_in_midi_drum = 0;
             m_direct = -1;

             if (thisline.size() > 6)
             {
                 m_dmap = AppendF(m_dmap, atof(thisline[7].c_str()));
                 if (atof(thisline[7].c_str()) > m_DATA_maxdelay) m_DATA_maxdelay = atof(thisline[7].c_str());
             }
             else
             {
                 m_dmap = AppendF(m_dmap, 0);
             }

             if (thisline.size() > 8)
             {
                 m_ipriomap = AppendI( m_ipriomap, atoi(thisline[9].c_str()));
             }
             else
             {
                 m_ipriomap = AppendI( m_ipriomap, 1);
             }

             if (thisline.size() > 11)
             {
                m_itrackdivide = AppendI(m_itrackdivide, atoi(thisline[11].c_str()));
                m_itrackdividepart = AppendI(m_itrackdividepart, atoi(thisline[12].c_str()));
             }
             else
             {
                m_itrackdivide = AppendI(m_itrackdivide, 1);
                m_itrackdividepart = AppendI(m_itrackdividepart, 0);
             }

             if (thisline.size() > 11)
             {
                 m_itrackdivide = AppendI(m_itrackdivide, atoi(thisline[11].c_str()));
                 m_itrackdividepart = AppendI(m_itrackdividepart, atoi(thisline[12].c_str()));
             }
             else
             {
                 m_itrackdivide = AppendI(m_itrackdivide, 1);
                 m_itrackdividepart = AppendI(m_itrackdividepart, 0);
             }
             if (thisline.size() > 15)
             {
                 m_imfmap = AppendI(m_imfmap, atoi(thisline[14].c_str()));
                 m_imsmap = AppendI(m_imsmap, atoi(thisline[15].c_str()));
             }
             else
             {
                 m_imfmap = AppendI(m_imfmap, 0);
                 m_imsmap = AppendI(m_imsmap, 0);
             }
         }
         if (thisline[0] == "voladjust")
         {
             m_voladjust = 1;
         }
         if (thisline[0] == "range")
         {
             m_defaultrange[0] = atoi(thisline[1].c_str());
             m_defaultrange[1] = atoi(thisline[2].c_str());
         }

         if (thisline[0] == "align")
         {
             m_ialign = atoi(thisline[1].c_str());
         }

         if (thisline[0] == "invert")
         {
             m_invertthis = 1;
         }
         if (thisline[0] == "humanizer")
         {
             m_mtd = atoi(thisline[1].c_str());
         }
      }
}
   }
   m_log << "Mapping file " << infilename << " loaded." << std::endl;

   // close the file, we are done reading
   myconfigfile.close();
}

#endif
