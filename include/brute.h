#ifndef BRUTE_H
#define BRUTE_H

//#include "chord.h"
#include "Options.h"
#include "MidiFile.h"
#include "configfile.h"
#include "chord.h"
#include "brutedefinitions.h"


#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>
#include <list>
#include <omp.h>
#include <sstream>


class Brute
{

public:
    void LoadMidi( char * mymidiname );
    void ExportOutAll( char * outfilename );

    void ExportDefaultConfig( char * outfilename ); // Routine to save the mapping to the out.config
    void GenerateDefaultConfig(); // Make the default mapping text internally

    void ImportConfig( char * infilename ); // Imports the mapping from out.config
    void ParseConfig(std::stringstream * text ); // Parses the internal config into the mapping information

    void PitchBends();
    void GenerateQuantizedNotes();
    void GenerateNoteSelection();
    void MapToRegister();
    void GenerateRoughChordLists();
    void ChordJoinDurations();
    void CorrectMissmatch();
    void CompensateEasy();
    void Check_for_too_long_tones();

    bool AllChordsOK();

    void GenerateDurationNames();

    void ExportABC(char * abcfilename);
    void GenerateABC();

    // config file ( out.config equivalent )
    ConfigFile m_Mapping;

    std::stringstream m_MappingText;  // internal out.config equivalent, contains the mapping information
    std::stringstream m_ABCText;


private:
    // MidiFile instance to deal with the midi file
    smf::MidiFile m_Midi;

    // list of midi channel instruments
    std::vector<int> m_midiinstruments;

    // list of drum or non-drum tracks in midi
    std::vector<bool> m_isdrumtrack;

    // tones per track
    std::vector<int> m_tonecounts;

    // midi tone events
    std::vector< std::vector<double> > m_tonestarts;
    std::vector< std::vector<double> > m_toneends;
    std::vector< std::vector<int> > m_pitches;
    std::vector< std::vector<int> > m_velocities;

    std::vector< std::vector < std::vector<bool> > > m_selected;

    // quantized midi events : [notestart, noteend, notestarterror, noteenderror]
    std::vector< std::vector < int64_t >> m_qnotestart;
    std::vector< std::vector < int64_t >> m_qnoteend;
    std::vector< std::vector < double >> m_qnotestarterror;
    std::vector< std::vector < double >> m_qnoteenderror;

    // global max tick
    double m_globalmaxtick;
    int m_globalminvel;
    int m_globalmaxvel;
    int64_t m_registerlength;

    // timing variables
    double m_division;
    double m_divmulti;
    double m_mididuration;
    int m_bpm;
    double m_BPM2;
    int    m_minstep;

    int m_qunits;
    int64_t m_maxduration;
    int m_minnotestart;

    int64_t m_verylasttone;
    int64_t m_verylasttonestart;

    // pitch statistics
    std::vector<int64_t> m_avpitches;
    std::vector<int64_t> m_avpitchc;

    // list of the pitches used in a track
    std::vector< std::vector < bool > > m_samplesused;


    // pitch bends info
    std::vector<int> m_pitchbendcounter;
    std::vector< std::vector < double > > m_pitchbendtimes;
    std::vector< std::vector < double > > m_pitchbendvalues;

    // default polyphony
    int m_maxchordnotes;

    // Register Information (mapped tones on lattice)

    // Tones - ABC Track -> Pitch -> Length
    std::vector< std::vector < std::vector < float > >  >m_register;  // is a tone playing (+priority)
    std::vector< std::vector < std::vector < float > >  >m_missmatch; // tone start missmatches in this slot
    std::vector< std::vector < std::vector < float > >  >m_velocity;  // velocity of the tone
    std::vector< std::vector < std::vector < float > >  >m_priomap;   // tone priorities to estimate missmatch and velocity per slot

    std::vector< std::vector <float> > m_projectedmissmatch; // overall missmatch in this
    std::vector< std::vector <float> > m_projectedvelocity;  // overall velocity in this

    // Chord information .. Track->Number->
    std::vector< std::list < ChordL > > m_chordlists;

    void Next_is_Break(int abctrack);
    void Absorb_Short_Breaks(int abctrack);
    void Next_tone_is_prolongued(int abctrack);
    void Short_Chord(int abctrack);
    void Long_enough_Chord_next_long_enough(int abctrack);
    void Short_following_long(int abctrack);
    void Two_shorts(int abctrack);

    int m_corrections;
    bool m_done;
};

// Midi File Loader
void Brute::LoadMidi(char * mymidiname)
{
    m_Midi = smf::MidiFile();  // make sure nothing is left from old midi

    m_Midi.read(mymidiname);

    // this would be the place to turn the midi from 0 to 1 format

    // initialize samples used statistics
    m_samplesused.resize(m_Midi.size());
    for (int i = 0; i < m_Midi.size(); i++)
    {
        m_samplesused[i].resize(256);
        for (unsigned int j = 0; j < m_samplesused[i].size(); j++)
            m_samplesused[i][j] = false;
    }

    // midi instruments of tracks
    m_midiinstruments.resize(m_Midi.size());
    for (int i = 0; i < m_Midi.size(); i++) m_midiinstruments[i] = 0;

    // number of tones per track
    m_tonecounts.resize(m_Midi.size());
    for (int i = 0; i < m_Midi.size(); i++) m_tonecounts[i] = 0;

    // drum track book keeping
    m_isdrumtrack.resize(m_Midi.size());
    for (int i = 0; i < m_Midi.size(); i++) m_isdrumtrack[i] = false;

    // reserve space for starts/ends/pitches/velocities
    m_tonestarts.resize(m_Midi.size());
    m_toneends.resize(m_Midi.size());
    m_pitches.resize(m_Midi.size());
    m_velocities.resize(m_Midi.size());

    // reserve tracks for pitchbend info
    m_pitchbendtimes.resize(m_Midi.size());
    m_pitchbendvalues.resize(m_Midi.size());

    // pitchbend arrays
    m_pitchbendcounter.resize(m_Midi.size());
    for (int i = 0; i < m_Midi.size(); i++) m_pitchbendcounter[i] = 0;


    //int ticksperbeat =  m_Midi.getTicksPerQuarterNote();
    m_bpm = 120; // initial default tempo

    double timetoticks = 0.630;

    //MidiEvent * ptr;
    m_Midi.absoluteTicks();
    m_Midi.doTimeAnalysis();

    // Velocity Measure
    int globalmaxvel = 0;
    int globalminvel = 255;

    // final tick value
    double globalmaxtick = 0;

    // to build the pitch averages for shifting everything to middle octave
    m_avpitches.resize(m_Midi.size());
    m_avpitchc.resize(m_Midi.size());

    // to keep the current volume
    int curvol = 64;


    // loop through midi file to find all the stuff
    for (int i = 0; i < m_Midi.size(); i++)
    {
        // set volume to default midi track volume
        curvol = 64;

        // Keep track of tones - store on-times and velocities per pitch
        std::vector<double> ontimes(128);
        std::vector<int> onvelocities(128);
        for (int j=0; j<128; j++)
        {
            ontimes[j] = -1.0;
            onvelocities[j] = -1;
        }

        // Loop over events in this track
        int eventcount = m_Midi.getEventCount(i);

        // resize all the arrays to the number of events .. just to be on the save side
        m_tonestarts[i].resize(eventcount);
        m_toneends[i].resize(eventcount);
        m_pitches[i].resize(eventcount);
        m_velocities[i].resize(eventcount);

        // pitchbend arrays
        m_pitchbendtimes[i].resize(eventcount);
        m_pitchbendvalues[i].resize(eventcount);


        for (int j = 0; j < eventcount; j++)
        {
            int command = m_Midi[i][j][0] & 0xf0;

            if ( m_Midi.getEvent(i, j).isTempo() & (m_Midi[i][j].tick == 0) )
            {
                m_bpm = m_Midi.getEvent(i,j).getTempoBPM();

            }

            // Commands to set the Midi Instrument ( always will use the last one )
            if ((command == 0xc0))
            {
                m_midiinstruments[i] = m_Midi[i][j][1];
            }

            // keep track of volume
            if (command == 0xb0)
            {
                if ( (int) m_Midi[i][j][1] == 7)
                {
                    // track volume change
                    curvol = (int) m_Midi[i][j][2];
                }
            }

            // This is a tone start
            if (command == 0x90 && m_Midi[i][j][2] != 0)
            {
                // store note-on velocity and time
                int key = m_Midi[i][j][1];
                int vel = m_Midi[i][j][2];

                int channel = m_Midi[i][j].getChannelNibble();
                if (channel == 9)
                {
                    m_isdrumtrack[i] = true;
                }

                ontimes[key] = timetoticks*m_Midi.getTimeInSeconds(m_Midi[i][j].tick);

                int myvel = vel + curvol;
                // keep track of global maximum
                if ( myvel > globalmaxvel ) globalmaxvel = myvel;
                if ( myvel < globalminvel ) globalminvel = myvel;

                if (myvel < 0) myvel = 0;
                onvelocities[key] = myvel;

                m_avpitches[i] += key;
                m_avpitchc[i] += 1;


            }
            else if (command == 0x90 || command == 0x80)
            {
                // this is a tone end

                int key = m_Midi[i][j][1];

                double offtime = timetoticks*m_Midi.getTimeInSeconds(m_Midi[i][j].tick);

                // this is a tone
                double starttime = ontimes[key]*26460.0;
                double endtime = offtime * 26460.0;
                int onvelocity = onvelocities[key];
                int pitch = key;

                // store in tone list
                m_tonestarts[i][m_tonecounts[i]] = starttime;
                m_toneends[i][m_tonecounts[i]] = endtime;
                m_velocities[i][m_tonecounts[i]] = onvelocity;
                m_pitches[i][m_tonecounts[i]] = pitch;

                if ( endtime > globalmaxtick ) globalmaxtick = endtime;
                m_tonecounts[i] += 1;
            }

            // check for pitch bend events
            if (m_Midi[i][j].isPitchbend() )
            {

                double time =timetoticks* m_Midi.getTimeInSeconds(m_Midi[i][j].tick) ;
                //int msb = m_Midi[i][j][3];
                int msb = 0;
                int lsb = m_Midi[i][j][2];
                double pitchwheel = ((lsb * 128 + msb)-(64*128))/8192.0;

                m_pitchbendtimes[i][ m_pitchbendcounter[i] ] = time;
                m_pitchbendvalues[i][ m_pitchbendcounter[i] ] = pitchwheel;

                m_pitchbendcounter[i]++;
            }
        }
        // collect samples used statistics
        for (unsigned int j = 0; j < ontimes.size(); j++)
            if (ontimes[j]>=0)
            {
                m_samplesused[i][j] = true;
            }
    }
    m_globalmaxtick = globalmaxtick;
    m_globalmaxvel = globalmaxvel;
    m_globalminvel = globalminvel;

    // switch this to constant stuff without midi values

    m_division = 1000;
    m_divmulti = 26460.0 / m_division;
    m_mididuration = globalmaxtick;
    m_minstep = 1000;

    // Set volumes to normalized max
    for (int i = 0; i < m_Midi.size(); i++)
        for (unsigned int j = 0; j < m_velocities[i].size(); j++)
            m_velocities[i][j] = m_velocities[i][j] - m_globalmaxvel + 127;
}

// Export the out_all.txt file with tone information
void Brute::ExportOutAll( char * outfilename)
{
    // Declare the file
    std::ofstream myallfile;
    myallfile.clear();
    myallfile.open(outfilename);

    myallfile << "# Instrumentmap" << std::endl;
    myallfile << m_Midi.size() << std::endl;
    for (int i = 0; i < m_Midi.size(); i++)
    {
        myallfile << miditolotro[(int)m_midiinstruments[i]]  << std::endl;
    }

    myallfile << "# Tracknotes" << std::endl;
    myallfile << m_Midi.size() << std::endl;

    for (int i = 0; i < m_Midi.size(); i++)
    {
        // std::cout << "# track " << i << std::endl;
        myallfile << "# track " << i << std::endl;
        myallfile << m_tonecounts[i] << std::endl;
        for (int j = 0; j < m_tonecounts[i]; j++)
        {
            myallfile
                    << std::fixed << std::setw(11) << std::setprecision(15)
                    << m_tonestarts[i][j]
                    << "  " << m_toneends[i][j]
                    << "  " << m_velocities[i][j]
                    << "  " << m_pitches[i][j]
                    << std::endl;
        }
    }

    myallfile << "# minstep" << std::endl;
    myallfile << m_minstep << std::endl;
    myallfile << "# totalduration" << std::endl;
    myallfile << int(m_globalmaxtick/27.367551593837806+1) << std::endl;
    myallfile << "# octavepitches" << std::endl;
    myallfile << int(m_Midi.size()) << std::endl;

    for (int i = 0; i < m_Midi.size(); i++)
    {
        //std::cout << int(double(avpitches[i])/double(avpitchc[i])/12 - 1) << std::endl;
        myallfile << int(double(m_avpitches[i])/double(m_avpitchc[i])/12 - 1) << std::endl;
    }

    myallfile << "# tracks" << std::endl;
    myallfile << m_Midi.size() << std::endl;
    for (int i = 0; i < m_Midi.size(); i++)
    {
        int a = 0;
        int b = 127;
        if (( i > 0 ) & ( m_midiinstruments[i] == 0)) a = 10;
        if ( i == 0) b = 0;
        // std::cout << a << " " << channelinstruments[i] << " " << b << std::endl;
        myallfile << a << " " << m_midiinstruments[i] << " " << b << std::endl;
    }

    myallfile << "# BPM" << std::endl;
    // std::cout << 120 << std::endl;
    myallfile<< 120 << std::endl;
    // std::cout << "# Maxvel " << std::endl;
    myallfile<< "# Maxvel " << std::endl;
    // std::cout << globalmaxvel - 2*127 << std::endl;
    myallfile<< m_globalmaxvel - 2*127 << std::endl;

    myallfile << "# Pitchbends" << std::endl;
    //std::cout << midifile.size()-1 << std::endl;
    myallfile << m_Midi.size()-1 << std::endl;

    for (int i = 1; i < m_Midi.size()-1; i++)
    {

        myallfile << m_pitchbendcounter[i]+1 << std::endl;

        myallfile << "0.0 0.0" << std::endl;
        for (int j = 0; j < m_pitchbendcounter[i]; j++)
        {
            myallfile
                    << m_pitchbendtimes[i][j] << "  " << m_pitchbendvalues[i][j] << std::endl;
        }
    }

    myallfile<< 2 << std::endl;
    //std::cout << 2 << std::endl;
    myallfile<< "0.0 0.0" << std::endl;
    //std::cout << "0.0 0.0" << std::endl;
    myallfile<< "0.0 0.0" << std::endl;
    //std::cout << "0.0 0.0" << std::endl;

    // close file
    myallfile.close();
}

// For compatibility this exports a config which corresponds to the midi tracks
void Brute::ExportDefaultConfig( char * outfilename )
{

    GenerateDefaultConfig();

    std::ofstream myconfigfile;
    myconfigfile.open(outfilename);

    myconfigfile << m_MappingText.rdbuf();;

    myconfigfile.close();

}

// For compatibility this exports a config which corresponds to the midi tracks
void Brute::GenerateDefaultConfig( )
{
    m_MappingText.str(std::string()); // Reset the Mapping Text

    // default.config values
    int drumtype = 0;
    char defaultdrumhandling[127] = "nosplit";
    char ABCstyle[127] = "Rocks";
    char defaulttranscriber[127] = "Himbeertony";
    char dummy[127];

    // check for default instrument mappings
    std::ifstream dinstrumentfile;
    dinstrumentfile.open("dinstruments.config");
    if (!dinstrumentfile.fail())
    {
        std::cout << "Using custom dinstruments.config file " << std::endl;
        std::string thisline;
        int pos = 0;

        while( !dinstrumentfile.fail() )
        {
            std::getline(dinstrumentfile, thisline);
            if (thisline.at(0) != '#')


                for (unsigned int j = 0; j < split(thisline,' ').size(); j++)
                {
                    std::string numberstring = split(thisline, ' ')[j];
                    int number = std::atoi( numberstring.c_str() );
                    miditolotro[pos] = number;
                    pos = pos + 1;
                }
        }
        std::cout << std::endl;
        dinstrumentfile.close();
    }

    // check for defaults file
    std::ifstream defaultsfile;
    defaultsfile.open("default.config");
    if (!defaultsfile.fail() )
    {
        std::cout << "Using default.config" << std::endl;
        defaultsfile >> dummy;
        defaultsfile >> drumtype >> defaultdrumhandling;
        defaultsfile >> dummy;
        defaultsfile >> ABCstyle;
        defaultsfile >> dummy;
        defaultsfile >> defaulttranscriber;
        defaultsfile.close();
    }
    else
    {
        std::cout << "No default.config, using intrinsic defaults" << std::endl;
        std::ofstream newdefaultsfile;
        newdefaultsfile.open("default.config");
        newdefaultsfile << "Drums: 0 nosplit" << std::endl;
        newdefaultsfile << "Style: Rocks" << std::endl;
        newdefaultsfile << "Transcriber:" << std::endl;
        newdefaultsfile << "Himbeertony" << std::endl;
        newdefaultsfile.close();
    }
    std::cout << "Drumstyle: " << drumtype << std::endl;
    std::cout << "Drumhandling: " << defaultdrumhandling << std::endl;
    std::cout << "ABC Style: " << ABCstyle << std::endl;
    std::cout << "Transcriber Name: " << defaulttranscriber << std::endl;

    bool drumsplitting = true;
    if (strcmp("nosplit", defaultdrumhandling) >= 0)
        drumsplitting = false;

    m_MappingText << "Name: <insert title>" << std::endl;
    m_MappingText << "Speedup: 0" << std::endl;
    m_MappingText << "Pitch: 0" << std::endl;

    // remark .. think about adding compressor values!!!

    m_MappingText << "Style: " << ABCstyle << "  % Defaults for -a rock and a hard place-, others: TSO, Meisterbarden, Bara" << std::endl;
    m_MappingText << "Volume: 0" << "       % scaled, midi volume was " << m_globalmaxvel - 254 << std::endl;

    m_MappingText << "Compress: 1.0" << "   % default : midi dynamics, between 0 and 1: smaller loudness differences, >1: increase loudness differences" << std::endl;
    m_MappingText << "%no pitch guessing   %uncomment to switch off guessing of default octaves" << std::endl;
    m_MappingText << "%no back folding     %uncomment to switch off folding of tone-pitches inside the playable region" << std::endl;
    m_MappingText << "fadeout length 0    %seconds before the end to start with fadeout (try something between 5 and 15)" << std::endl;
    m_MappingText << "Transcriber " << defaulttranscriber << std::endl;
    m_MappingText << std::endl;
    m_MappingText << std::endl;

    for (int i = 0; i < m_Midi.size(); i++)
    {
        if ( m_tonecounts[i] > 0)
        {
            m_MappingText << "abctrack begin" << std::endl;
            m_MappingText << "%voladjust    %uncomment to try automatic compensation for U16.1 volumes (experimental!)" << std::endl;
            m_MappingText << "polyphony 6 top  % options: top removes tones from higher pitch first, bottom lower pitch first" << std::endl;

            m_MappingText << "duration 2" << std::endl;
            m_MappingText << "panning 64" << std::endl;



            m_MappingText << "% panning 64 is stereo center, values range from 0 (far left) to 127 (far right) - used in audio preview" << std::endl;
            if (!m_isdrumtrack[i])
            {
                m_MappingText << "instrument " << lotroinstruments[miditolotro[m_midiinstruments[i]]] << std::endl;
                m_MappingText << "%Original Midi Instrument: " << m_midiinstruments[i] << "  " << GMinstrument[m_midiinstruments[i]] << std::endl;
                m_MappingText << "miditrack " << i <<  " pitch 0 " << " volume 0 " << " delay 0 " << " prio 1 " << std::endl;
            }
            else
            {
                m_MappingText << "instrument drums " << drumtype << std::endl;
                // inform about the drum samples used
                m_MappingText << "% ";
                for (unsigned int m=0; m < m_samplesused[i].size(); m++)
                    if (m_samplesused[i][m]) m_MappingText << m << ":" << GMdrumnames[m] << "  ";
                m_MappingText << std::endl;

                if (drumsplitting)
                {
                    for (unsigned int m= 0; m < m_samplesused[i].size(); m++)
                        if (m_samplesused[i][m])
                        {
                            m_MappingText << "instrument drums " << drumtype << " " << m << std::endl;
                            m_MappingText << "miditrack " << i << " pitch 0 " << " volume 0 " << " delay 0" << std::endl;
                        }
                }
                else
                {
                    m_MappingText << "miditrack " << i <<  " pitch 0 " << " volume 0 " << " delay 0" << std::endl;
                }
            }



            m_MappingText << "abctrack end" << std::endl;
            m_MappingText << std::endl;
        }
    }
}


// For compatibility import a config File
void Brute::ImportConfig( char * infilename )
{
    // just set the max chords to 6
    m_maxchordnotes = 6;

    // Find all those drum maps
    m_Mapping.ImportDrumMaps();

    // open the out.config file
    m_Mapping.ImportConfigFile(infilename);

    // open the pitchbend.config file
    m_Mapping.ImportPitchBendInstructions();
}

// For compatibility import a config File
void Brute::ParseConfig(std::stringstream * mappingtext)
{
    // just set the max chords to 6
    m_maxchordnotes = 6;

    // Find all those drum maps
    m_Mapping.ImportDrumMaps();

    // open the out.config file
    m_Mapping.ParseConfigMapping(mappingtext);

    // open the pitchbend.config file
    m_Mapping.ImportPitchBendInstructions();
}

void Brute::GenerateQuantizedNotes()
{
    // this is where the quantization happens
    // every midi tone is thrown on the intrinsic lattice in time

    m_maxduration = 0;
    m_minnotestart = 0; // magic number: 2^30

    // now we do some regularization math
    int zminstep = m_minstep/m_Mapping.m_oversampling;  // oversampling should be always 2
    m_qunits = 8 * zminstep;
    double ziminstep = 1.0 / zminstep;

    m_verylasttone = 0;
    m_verylasttonestart = 0;

    // we may not need this always, but nothing wrong with declaring a bit too much
    double oldhuman = 0;
    double oldhuman2 = 0;
    double oldhuman3 = 0;

    // build the normal distribution rng
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,m_Mapping.m_dohumanization);

    // traditionally here would be some calculations for time correction of instruments, not beeing done right now
    m_qnotestart.resize(m_Midi.size());
    m_qnoteend.resize(m_Midi.size());

    m_qnotestarterror.resize(m_Midi.size());
    m_qnoteenderror.resize(m_Midi.size());

    // loop over midi tracks
    for (int i=0; i < m_Midi.size(); i++)
    {
        // allocate memory for quantized tones
        int tonesinthistrack = m_tonecounts[i];

        m_qnotestart[i].resize( tonesinthistrack );
        m_qnoteend[i].resize( tonesinthistrack );
        m_qnotestarterror[i].resize( tonesinthistrack);
        m_qnoteenderror[i].resize( tonesinthistrack);

        // loop over tones in midi track
        for (int j = 0; j < tonesinthistrack; j++)
        {
            // someone crazy switched on the humanization - because this is a not usual thing, we just change the timings
            // in the midi tones. The oldhuman variables are a lag filter to avoid too fast jumps in timing missmatch
            if (m_Mapping.m_dohumanization > 0.)
            {
                double r_start = m_tonestarts[i][j];
                double r_end = m_toneends[i][j];

                double mtdshift = distribution(generator);
                r_start = r_start + (mtdshift+oldhuman+oldhuman2*0.35+oldhuman3*0.15)*0.4;
                r_end = r_end + (mtdshift+oldhuman+oldhuman2*0.35+oldhuman3*0.15)*0.4;

                // some kind of cheap mans ringbuffer
                oldhuman3 = oldhuman2;
                oldhuman2 = oldhuman;
                oldhuman = mtdshift;

                m_toneends[i][j] = r_end;
                m_tonestarts[i][j] = r_start;
            }

            // keep track of final tone
            if (m_toneends[i][j] > m_verylasttone) m_verylasttone = m_toneends[i][j];
            if (m_tonestarts[i][j] > m_verylasttonestart) m_verylasttonestart = m_tonestarts[i][j];

            // bin number in register grid for this tone
            int64_t qstart = static_cast<int64_t>( m_tonestarts[i][j] * ziminstep  );
            int64_t qend   = static_cast<int64_t>( m_toneends[i][j] * ziminstep );

            // keep track of rounding error
            double qstarterror = (m_tonestarts[i][j]*ziminstep) - qstart ;
            double qenderror   = (m_toneends[i][j]*ziminstep) - qend;

            //std::cout << qstart << "  " << qstarterror << std::endl;

            // store in quantized vectors
            m_qnotestarterror[i][j] = qstarterror;
            m_qnoteenderror[i][j] = qenderror;
            m_qnotestart[i][j] = qstart;
            m_qnoteend[i][j] = qend;

            if (qend > m_maxduration) m_maxduration = qend + m_Mapping.m_DATA_maxdelay;
        }
    }

    // setting some constants
    m_minnotestart /= m_Mapping.m_oversampling;
    m_qunits *= m_Mapping.m_oversampling * m_Mapping.m_oversampling / 2;
}

void Brute::PitchBends()
{
    // not done right now!
}


void Brute::MapToRegister()
{
    // this maps the quantized tones to the register

    // Allocate Registers
    m_registerlength = m_maxduration+1+100;

    int nabctracks = static_cast<int>( m_Mapping.m_instrumap.size() );

    // allocate and wipe memory for registers
    // Tones - ABC Track -> Pitch -> Length

    m_register.resize(nabctracks);
    m_missmatch.resize(nabctracks);
    m_velocity.resize(nabctracks);
    m_priomap.resize(nabctracks);

    m_projectedmissmatch.resize(nabctracks);
    m_projectedvelocity.resize(nabctracks);

    for (int i = 0; i < nabctracks; i++)
    {
        m_projectedmissmatch[i].resize(m_registerlength);
        m_projectedvelocity[i].resize(m_registerlength);
        for (int j = 0; j < m_registerlength; j++)
        {
            m_projectedmissmatch[i][j]=0.;
            m_projectedvelocity[i][j]=0.;
        }
    }

    for (int i = 0; i < nabctracks; i++)
    {
        m_register[i].resize(38);
        m_missmatch[i].resize(38);
        m_velocity[i].resize(38);
        m_priomap[i].resize(38);

        for (int pitch = 0; pitch < 38; pitch++)
        {
            m_register[i][pitch].resize(m_registerlength);
            m_missmatch[i][pitch].resize(m_registerlength);
            m_velocity[i][pitch].resize(m_registerlength);
            m_priomap[i][pitch].resize(m_registerlength);
            for (int j = 0; j < m_registerlength; j++)
            {
                m_register[i][pitch][j] = 0.;
                m_missmatch[i][pitch][j] = -1.;
                m_velocity[i][pitch][j] = 0.;
                m_priomap[i][pitch][j] = 0.;
            }
        }
    }

    // Now write all the tones in the register

    // Loop over all abctracks
    m_log << "Mapping Info " << std::endl;
  //  #pragma omp parallel for
    for (int abctrack = 0; abctrack < nabctracks; abctrack++)
    {
        // Loop over the miditracks in this abctrack
        for (unsigned int miditrack = 0; miditrack < m_Mapping.m_trackmap[abctrack].size(); miditrack++ )
        {
            int utrack = m_Mapping.m_trackmap[abctrack][miditrack];
            m_log << "ABC Track: " << abctrack+1 << " Miditrack: " << utrack << std::endl;;

            int octavepitch;
            if (m_avpitchc[utrack]!=0)
            {
                octavepitch = int(double(m_avpitches[utrack])/double(m_avpitchc[utrack])/12 - 1);
            }
            else
            {
                octavepitch = 0;
            }
            if ( m_Mapping.m_nopitchguessing ) octavepitch = 0;

            for (int toneid = 0; toneid < m_tonecounts[utrack]; toneid++)
            {
                bool takethistone = true;

                // velocity is the normalized velo from the midi reading
                int velocity = m_velocities[utrack][toneid] + m_Mapping.m_volumemap[abctrack][miditrack];
                // std::cout << m_Mapping.m_volumemap[abctrack][miditrack] << std::endl;

                // pitch, adjusted by general pitch, per midi pitch and possible octave guessing
                int pitch;

                // now fold or not fold the pitch into playable region
                //    if (  !m_isdrumtrack[utrack] ) // this would be the miditrack info, but we use definitions in config file!
                if ( m_Mapping.m_instrumap[abctrack] != 8 )
                {
                    pitch = m_pitches[utrack][toneid] + m_Mapping.m_generalpitch + m_Mapping.m_pitchmap[abctrack][miditrack] -
                            octavepitch * 12;
                    while ( pitch < m_Mapping.m_rangemapl[abctrack][miditrack] ) pitch = pitch + 12;
                    while ( pitch > m_Mapping.m_rangemaph[abctrack][miditrack] ) pitch = pitch - 12;

                    // here would be the tonality conversion, but could be done later!
                }
                else
                {
                    // drums use the mapping
                    pitch = m_Mapping.m_drumsmapd[m_Mapping.m_drumstylemap[abctrack][miditrack]][m_pitches[utrack][toneid]];

                    // check for drum sample selection
                    if (m_Mapping.m_drumsingleinstrument[abctrack][miditrack] > 0)
                        if (m_pitches[utrack][toneid]!=m_Mapping.m_drumsingleinstrument[abctrack][miditrack]) takethistone = false;
                }



                if ((takethistone)&&(m_selected[abctrack][miditrack][toneid]))
                    // if (takethistone)
                {
                    double mystart = m_qnotestart[utrack][toneid] - m_minnotestart + m_Mapping.m_delaymap[abctrack][miditrack];
                    double myend   = m_qnoteend[utrack][toneid] - m_minnotestart + m_Mapping.m_delaymap[abctrack][miditrack];

                    // assure minimum note and maximum note length
                    while ( (myend - mystart) < m_Mapping.m_durmap[abctrack] )
                    {
                        myend = myend + 1;
                    }
                    while ( ((myend - mystart) > m_Mapping.m_durmaxmap[abctrack]) && (myend-mystart >= m_Mapping.m_durmap[abctrack]) ) myend = myend -1;

                    // Linear 'note'-priority-decay from start to end (rather shorten a tone than miss out on a new start)
                    // v(end-start) = x/(end-start)
                    double m = 1.0 / (myend-mystart);
                    double endp1 = myend + 1;


                    // keep track of missmatch, if tone is already assigned, give a warning and use missmatch of first
                    if ((pitch >= 0) && (pitch < 38))
                    {

                        if (m_missmatch[abctrack][pitch][mystart] >= 0.)
                        {

                            if ( !dequal( m_missmatch[abctrack][pitch][mystart], m_qnotestarterror[utrack][toneid] ) )
                            {
                                m_log << "Identical pitch, start times aligned: " << utrack << " time: " << maketime(m_tonestarts[utrack][toneid]) << "    Difference: "  << maketime( std::abs(m_qnotestarterror[utrack][toneid] - m_missmatch[abctrack][pitch][mystart]) ) << std::endl;
                            }
                        }
                        else
                        {
                            m_missmatch[abctrack][pitch][mystart] = m_qnotestarterror[utrack][toneid];  // first tone in this register wins the race
                        }


                        if ( velocity > m_velocity[abctrack][pitch][mystart] )
                        {
                            if ( m_velocity[abctrack][pitch][mystart] > 0)
                                std::cout <<"Identical pitch, taking highest velocity, Miditrack: " << utrack << " time: " << maketime(m_tonestarts[utrack][toneid]) << std::endl;
                            m_velocity[abctrack][pitch][mystart] = velocity;
                        }
                        // and mark the following slots till tone ends
                        for (int j = mystart; j < myend; j++)
                        {
                            double gm_val = (endp1 - j) * m + m_Mapping.m_priomap[abctrack][miditrack];
                            if (m_register[abctrack][pitch][j] < gm_val) m_register[abctrack][pitch][j] = gm_val;
                        }
                    }
                }
            }
        }

    }
    m_log << "Mapped tones to registers " << std::endl;
    // pitch = int( qtracknotes[track][i][3] - octavepitch[track] * 12 + pitchmap[itrack][utrack] + generalpitch )
}

void Brute::GenerateRoughChordLists()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());
    // reserve a list for every ABC track
    m_log << "Breaking registers into chords." << std::endl;
    m_chordlists.resize( abctracks );  // one list per track
    //#pragma omp parallel for
    for (int abctrack = 0; abctrack < abctracks; abctrack++)
    {
        // make chord, decide how long it is and then put it to the list
        // at this stage we loose some velocity and missmatch info

        // make sure to wipe chords from a former run
        m_chordlists[abctrack].clear();

        // first chord is special ( no continuation check )
        {
            ChordL mychord;
            mychord.velocity = 0;
            mychord.missmatch = 0.;
            mychord.duration = 1.0;
            mychord.is_rest = true;
            mychord.durationstring = "";
            mychord.ChordName = "";
            std::list<double> missmatches;

            for (int pitch = 0; pitch < 38; pitch++)
            {
                if ( m_register[abctrack][pitch][0]  > 0. )
                {
                    // this is a tone
                    mychord.npitches.push_back(pitch);
                    missmatches.push_back(m_missmatch[abctrack][pitch][0]);
                    if ( m_velocity[abctrack][pitch][0] > mychord.velocity )
                    {
                        mychord.velocity = m_velocity[abctrack][pitch][0];
                        mychord.missmatch = m_missmatch[abctrack][pitch][0];
                    }
                }
            }
            // now check if missmatches have been not agreeing
            double totalMRMS = 0.;
            for ( std::list<double>::iterator it = missmatches.begin(); it != missmatches.end(); it++ )
            {
                totalMRMS += (*it -  mychord.missmatch )*(*it - mychord.missmatch);
            }
            totalMRMS = std::pow(totalMRMS /  missmatches.size(), 0.5);
            if (totalMRMS > 0.00001) m_log << "Chord Merging at " << 0 << " total Error: " << totalMRMS << std::endl;
            if ( mychord.npitches.size() > 0 ) mychord.is_rest = false;

            // finally add this chord to the list
            m_chordlists[abctrack].push_back(mychord);
        }


        unsigned int currentposition = 1;
        while (currentposition < m_register[abctrack][0].size())
        {
            ChordL mychord;
            mychord.velocity = 0;
            mychord.missmatch = 0.;
            mychord.duration = 1.0;
            mychord.is_rest = true;
            mychord.original_starting_time = currentposition;
            std::list<double> missmatches;

            for (int pitch = 0; pitch < 38; pitch++)
            {
                if ( m_register[abctrack][pitch][currentposition]  > 0. )
                {
                    // this is a tone - we need to distinguish if this is a new one or a continued one
                    if (m_register[abctrack][pitch][currentposition] < m_register[abctrack][pitch][currentposition-1])
                    {
                        mychord.cpitches.push_back(pitch);
                    }
                    else
                    {
                        // only new tones dominate missmatch and velocity
                        mychord.npitches.push_back(pitch);
                        missmatches.push_back(m_missmatch[abctrack][pitch][currentposition]);
                        if ( m_velocity[abctrack][pitch][currentposition] > mychord.velocity )
                        {
                            mychord.velocity = m_velocity[abctrack][pitch][currentposition];
                            mychord.missmatch = m_missmatch[abctrack][pitch][currentposition];
                        }
                    }
                }
            }

            // now check if missmatches have been not agreeing
            double totalMRMS = 0.;
            for ( std::list<double>::iterator it = missmatches.begin(); it != missmatches.end(); it++ )
            {
                totalMRMS += (*it -  mychord.missmatch )*(*it - mychord.missmatch);
            }
            totalMRMS = std::pow(totalMRMS /  missmatches.size(), 0.5);
            if (totalMRMS > 0.00001) m_log << "ABCT: " << abctrack << " Chord Merge at " << currentposition << " Error: " << totalMRMS << std::endl;
            if ( mychord.npitches.size() + mychord.cpitches.size() > 0 ) mychord.is_rest = false;
            m_chordlists[abctrack].push_back(mychord);
            currentposition = currentposition+1;
        }
    }
}

// this is the most harmless action that checks for purely continued elements
void Brute::ChordJoinDurations()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    // Loop over ABC Tracks
   // #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        // std::cout << m_chordlists[abctrack].size() << std::endl;
        std::list<ChordL>::iterator current;
        std::list<ChordL>::iterator former;
        std::list<ChordL>::iterator next;
        current = m_chordlists[abctrack].begin();
        former = current;
        next = current;
        next++;

        int deletelast = 0;

        while ( current != m_chordlists[abctrack].end())
        {
            bool did_I_do_something = false;

            // if this is a break and next is a break .. we can fuse them
            if (next != m_chordlists[abctrack].end())
                if (next->is_rest && current->is_rest)
                {
                    //std::cout << " 2 breaks " << std::endl;
                    current->duration = current->duration + next->duration;
                    if ( next != m_chordlists[abctrack].end() )
                    {
                        m_chordlists[abctrack].erase(next);
                        did_I_do_something = true;
                        if (current != m_chordlists[abctrack].begin())
                        {
                            current = former;
                        }
                        next = current;
                        next++;
                    }
                    else
                    {
                        // we have to take out the final member!
                        deletelast = 1;
                    }
                }

            // if both arent breaks and next is just continued we can merge as well
            if (next != m_chordlists[abctrack].end())
            {
                if ( (!next->is_rest && !current->is_rest) && ( next->npitches.size() == 0 ) && (next->cpitches.size() == current->npitches.size() + current->cpitches.size()) )
                {
                    //std::cout << " merging " << std::endl;
                    current->duration = current->duration + next->duration;
                    if ( next != m_chordlists[abctrack].end() )
                    {
                        m_chordlists[abctrack].erase(next);
                        did_I_do_something = true;
                        if (current != m_chordlists[abctrack].begin())
                        {
                            current = former;
                        }
                        next = current;
                        next++;
                    }
                    else
                    {
                        // we have to take out the final member!
                        deletelast = 1;
                    }
                }
            }
            if (!did_I_do_something)
            {
                if ( current != m_chordlists[abctrack].end() ) former = current;
                if ( current != m_chordlists[abctrack].end() ) current++;
                if ( current != m_chordlists[abctrack].end() ) next++;
            }
        }
        if (deletelast == 1) m_chordlists[abctrack].pop_back();

        // std::cout << m_chordlists[abctrack].size() << std::endl;
    }
}

void Brute::CorrectMissmatch()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    m_log << "Correcting starting times for chords." << std::endl;
    // Loop over ABC Tracks
   // #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        // Missmatch of first slot is an issue, we just ignore it!
        m_chordlists[abctrack].begin()->missmatch = 0.;

        std::list<ChordL>::iterator current;
        std::list<ChordL>::iterator former;
        std::list<ChordL>::iterator next;
        former = m_chordlists[abctrack].begin();
        current = former;
        current++;
        next = current;
        next++;

        while ( current != m_chordlists[abctrack].end())
        {
            // the current missmatch can be compensated by prolonging the preceeding tone and shortening the duration of this chord
            former->duration += current->missmatch;
            current->duration -= current->missmatch;
            current->missmatch = 0;

            former = current;
            current++;
            next = current;
            if ( current!= m_chordlists[abctrack].end()) next++;
        }
    }
}

void join_chords(std::list<ChordL>::iterator target, std::list<ChordL>::iterator source)
{
    // join continues pitches
    for (std::list<int>::iterator checko = source->cpitches.begin(); checko!=source->cpitches.end(); checko++ )
    {
        int isitnotin = 0;
        for (std::list<int>::iterator checknext = target->cpitches.begin(); checknext!=target->cpitches.end(); checknext++)
        {
            if (*checko==*checknext) isitnotin = 1;
        }
        if (isitnotin == 0) target->cpitches.push_back(*checko);
    }

    // join new pitches
    for (std::list<int>::iterator checko = source->npitches.begin(); checko!=source->npitches.end(); checko++ )
    {
        int isitnotin = 0;
        for (std::list<int>::iterator checknext = target->npitches.begin(); checknext!=target->npitches.end(); checknext++)
        {
            if (*checko==*checknext) isitnotin = 1;
        }
        if (isitnotin == 0) target->npitches.push_back(*checko);
    }

    // take higher velocity
    if (target->velocity < source->velocity ) target->velocity = source->velocity;

    // add duration to target
    target->duration = target->duration + source->duration;

}

void Brute::Absorb_Short_Breaks(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;

    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            if  (current->is_rest)
            {
                m_corrections += 1;
                // this is a too short break, just delete it and add duration to former tone
                former->duration = former->duration + current->duration;
                m_chordlists[abctrack].erase(current);
                current = former;
                if (current!=m_chordlists[abctrack].end()) current++;
                next = current;
                if (next!=m_chordlists[abctrack].end()) next++;
            }
        }
        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}


void Brute::Next_is_Break(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true; // assuming we are done

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false; // obviously we are not done
            if  ( (next->is_rest) )
            {
                m_corrections += 1;
                // next break is long enough to compensate
                if ( next->duration + current->duration >=4.0)
                {
                    next->duration = next->duration - (2.0 - current->duration);
                    current->duration =2.0;
                }
                else
                {
                    // next break is too short, so we absorb it
                    current->duration = current->duration + next->duration;
                    m_chordlists[abctrack].erase(next);
                    next = current;
                    if (next != m_chordlists[abctrack].end()) next ++;
                }
            }
        }
        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}



void Brute::Next_tone_is_prolongued(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            // for better understanding write out all the chord info
            if (next->npitches.size()==0)
            {
                // std::cout << "Next chord has no new tone, corrected" << std::endl;
                m_corrections += 1;

                if ( next->duration + current->duration >=4.0)
                {
                    next->duration = next->duration - (2.0 - current->duration);
                    current->duration =2.0;
                }
                else
                {
                    current->duration = current->duration + next->duration;
                    m_chordlists[abctrack].erase(next);
                    next = current;
                    if (next != m_chordlists[abctrack].end()) next ++;
                }
            }
        }

        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}

void Brute::Short_Chord(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            if (current->duration <= 1.0)
            {
                m_log << "Chord is very short, absorbing to following tone" << std::endl;
                m_corrections += 1;
                join_chords(next, current); // absorbs current into next
                m_chordlists[abctrack].erase(current);

                current = former;
                current++;
                next = current;
                next++;
            }
        }
        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}

void Brute::Long_enough_Chord_next_long_enough(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            if ((current->duration > 1.0)&&(current->duration < 2.0))
            {
                if (next->duration + current->duration > 4.0)
                {
                    m_corrections += 1;
                    m_log  << "Chord is longer than half, shifting next chord a bit later" << std::endl;
                    next->duration = next->duration - (2.0 - current->duration);
                    current->duration = 2.0;
                }
            }
            former = current;
            if ( current!= m_chordlists[abctrack].end()) current++;
            next = current;
            if ( current!= m_chordlists[abctrack].end()) next++;
        }

        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}

void Brute::Short_following_long(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            if (current->duration + former->duration >= 4.0)
            {
                m_corrections += 1;
                m_log << "Short tone, following long, moving short tone earlier in time " << std::endl;
                former->duration = former->duration - (2.0 - current->duration);
                current->duration = 2.0;
            }
            former = current;
            if ( current!= m_chordlists[abctrack].end()) current++;
            next = current;
            if ( current!= m_chordlists[abctrack].end()) next++;
        }

        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}

void Brute::Two_shorts(int abctrack)
{
    std::list<ChordL>::iterator current;
    std::list<ChordL>::iterator former;
    std::list<ChordL>::iterator next;
    former = m_chordlists[abctrack].begin();
    current = former;
    current++;
    next = current;
    next++;
    m_corrections = 0;
    m_done = true;

    while ( next != m_chordlists[abctrack].end())
    {
        // the current duration is too short
        if (current->duration < 2.0)
        {
            m_done = false;
            if ((current->duration + former->duration < 4.0))
            {
                m_corrections += 1;
                m_log << "For lack of other options: absorbing current chord to former one " << abctrack << std::endl;
                join_chords(former, current);
                m_chordlists[abctrack].erase(current);
                current = former;
                if (current!= m_chordlists[abctrack].end()) current++;
                next = current;
                if (next != m_chordlists[abctrack].end()) next++;
            }
        }
        former = current;
        if ( current!= m_chordlists[abctrack].end()) current++;
        next = current;
        if ( current!= m_chordlists[abctrack].end()) next++;
    }
}

void Brute::Check_for_too_long_tones()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());
    m_log << "Checking for max duration." << std::endl;

    #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {

        std::list<ChordL>::iterator current;
        std::list<ChordL>::iterator former;
        current = m_chordlists[abctrack].begin();
        former = current;

        while (current != m_chordlists[abctrack].end())
        {
            if (current->duration > 64)
            {
                // create a new chord that is only continued, make this one shorter and insert new chord
                ChordL newchord;

                // newchord just continues all the tones
                for ( std::list<int>::iterator tones = current->npitches.begin(); tones!=current->npitches.end(); tones++)
                    newchord.cpitches.push_back(*tones);
                for ( std::list<int>::iterator tones = current->cpitches.begin(); tones!=current->cpitches.end(); tones++)
                    newchord.cpitches.push_back(*tones);
                newchord.is_rest = current->is_rest;
                newchord.missmatch = 0;
                newchord.duration = 32.0;
                current->duration = current->duration - 32.0;
                newchord.velocity = current->velocity;
                former = current;
                former ++;
                m_chordlists[abctrack].insert(former, newchord);

            }
            else
            {
                current++;
            }
        }
    }
}

void Brute::CompensateEasy()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    m_log << "Correcting starting times for chords." << std::endl;
    // Loop over ABC Tracks
    //#pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        // Missmatch of first slot is an issue, we just ignore it!
        m_chordlists[abctrack].begin()->missmatch = 0.;

        // just make sure the final tone doesn't cause any issues
        std::list<ChordL>::iterator position = m_chordlists[abctrack].end();
        if (position!=m_chordlists[abctrack].begin())
        {
            position--;
            if (position->duration < 2.0) position->duration = 4.0;
        }

        // keep track of correction level .. always start and repeat the simple stuff first
        int correctionlevel = 0;
        m_done = false;

        while (!m_done)
        {
            // Level 0: Absorb Short Breaks
            if ((correctionlevel == 0) & (!m_done)) Absorb_Short_Breaks(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // Level 1: Use a following Break to prolongue too short tone
            if ((correctionlevel == 1) & (!m_done)) Next_is_Break(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // Level 2: See if next tone has no newly starting tones
            if ((correctionlevel == 2) & (!m_done)) Next_tone_is_prolongued(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // these are the nasty corrections

            // Level 3: current Chord is very short, absorbing to following tone
            if ((correctionlevel == 3) & (!m_done)) Short_Chord(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // Level 4: chord is longer than half, next chord is long enough to compensate
            if ((correctionlevel == 4) & (!m_done)) Long_enough_Chord_next_long_enough(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // Level 5: Short tone, following long, moving short tone earlier in time
            if ((correctionlevel == 5) & (!m_done)) Short_following_long(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            // Level 6: For lack of other options: absorbing current chord to former one
            if ((correctionlevel == 6) & (!m_done)) Two_shorts(abctrack);
            if (m_corrections > 0) correctionlevel = 0;
            if (m_corrections == 0) correctionlevel += 1;

            if ((correctionlevel == 7) & (!m_done)) std::cout << " we are out of ideas .. Track  "<< abctrack << std::endl;
            if ((correctionlevel == 7) & (!m_done)) correctionlevel = 0;
        }
    }
}

bool Brute::AllChordsOK()
{
    bool returnvalue = true;
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    // Loop over ABC Tracks
    #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        std::list<ChordL>::iterator current;
        current = m_chordlists[abctrack].begin();

        // first we do changes that don't affect starting times
        while ( current != m_chordlists[abctrack].end())
        {
            if (current->duration < 2.0) returnvalue = false;
            current++;
        }
    }
    return returnvalue;
}


void Brute::GenerateDurationNames()
{
    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    // Loop over ABC Tracks
    #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        std::list<ChordL>::iterator current;
        current = m_chordlists[abctrack].begin();
        double myerror = 0.;

        while ( current != m_chordlists[abctrack].end())
        {
            double thisduration = (current->duration*1000.0) / 2.0 + myerror;  // this is for base 8
            myerror = thisduration - int(thisduration);
            int value = int(thisduration);
            int base  = 8 * 1000;
            int divisor = gcd(value,base);
            value = value / divisor;
            base = base / divisor;
            current->length = value;
            current->denominator = base;
            current->durationstring = std::to_string(value) + "/" + std::to_string(base);
            current++;
        }
    }


    // Loop over ABC Tracks to make sure we have the correct number of tones and all
    #pragma omp parallel for
    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        std::list<ChordL>::iterator current;
        current = m_chordlists[abctrack].begin();

        while ( current != m_chordlists[abctrack].end())
        {
            // check if there is the same pitches in new and continued, if so delete the continued ones!
            for ( std::list<int>::iterator a = current->npitches.begin(); a != current->npitches.end(); a++)
                for ( std::list<int>::iterator b = current->cpitches.begin(); b != current->cpitches.end(); b++)
                    if ( *a == *b )
                    {
                        current->cpitches.erase(b);
                        b = current->cpitches.begin();
                    }
            current++;
        }

        // now make sure we adhere to the polyphony!
        current = m_chordlists[abctrack].begin();
        // second run over to assure polyphony
        while ( current != m_chordlists[abctrack].end())
        {
            if ( current->cpitches.size() + current->npitches.size() > static_cast<unsigned int>(m_Mapping.m_polymap[abctrack]) )
            {
                // new pitches are already too many, wiping all cpitches and important npitches
                if ( current->npitches.size() >= static_cast<unsigned int>( m_Mapping.m_polymap[abctrack] ) )
                {
                    while (current->cpitches.size() > 0) current->cpitches.pop_back();

                    int n = current->npitches.size() - m_Mapping.m_polymap[abctrack];

                    while (n > 0)
                    {
                        // find next cpitch to delete
                        std::list<int>::iterator gothrough;
                        std::list<int>::iterator best;
                        int value = *current->npitches.begin();
                        int direction = m_Mapping.m_polymapdir[abctrack];


                        for (gothrough = current->npitches.begin(); gothrough != current->npitches.end(); gothrough++)
                        {
                            if (( value < *gothrough )&&(direction==0))
                            {
                                value = *gothrough;
                            }
                            if ((value > *gothrough)&&(direction==1))
                            {
                                value = *gothrough;
                            }
                        }
                        for (gothrough = current->npitches.begin(); gothrough != current->npitches.end(); gothrough++)
                        {
                            if (value == *gothrough)
                            {
                                current->npitches.erase(gothrough);
                                break;
                            }
                        }
                        n = n - 1;
                    }
                }
                else
                {
                    // cpitches are enough to cancel .. we can just through out cpitches first
                    int n = current->npitches.size() + current->cpitches.size() - m_Mapping.m_polymap[abctrack];

                    while (n > 0)
                    {
                        // find next cpitch to delete
                        std::list<int>::iterator gothrough;
                        std::list<int>::iterator best;
                        int value = *current->cpitches.begin();
                        int direction = m_Mapping.m_polymapdir[abctrack];


                        for (gothrough = current->cpitches.begin(); gothrough != current->cpitches.end(); gothrough++)
                        {
                            if (( value < *gothrough )&&(direction==0))
                            {
                                value = *gothrough;
                            }
                            if ((value > *gothrough)&&(direction==1))
                            {
                                value = *gothrough;
                            }
                        }
                        for (gothrough = current->cpitches.begin(); gothrough != current->cpitches.end(); gothrough++)
                        {
                            if (value == *gothrough)
                            {
                                current->cpitches.erase(gothrough);
                                break;
                            }
                        }
                        n = n - 1;
                    }
                    // std::cout << current->cpitches.size() + current->npitches.size() << std::endl;
                }
            }
            current++;
        }
    }
}

void Brute::GenerateABC()
{
    m_ABCText.str(std::string()); // reset the string stream containing the ABC file text

    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());

    m_ABCText << "% Produced with Bruzo's Transcoding Environment 2.0 alpha " << std::endl;
    m_ABCText << "% Transcribed by " << m_Mapping.m_transcribername << std::endl;
    m_ABCText << std::endl;

    for (int abctrack=0; abctrack < abctracks; abctrack++)
    {
        // header
        m_ABCText << "X:" << abctrack+1 << std::endl;
        m_ABCText << "T: " << m_Mapping.m_songname  << " part " << abctrack+1 << "/" << abctracks << " [" << lotroinstruments[m_Mapping.m_instrumap[abctrack]] << "]" << std::endl;
        m_ABCText << "Z: Transcribed with BruTE " << m_Mapping.m_panningmap[abctrack] << std::endl;
        m_ABCText << "L: 1/4" << std::endl;
        m_ABCText << "Q: 125" << std::endl;
        m_ABCText << "K: C" << std::endl;

        std::list<ChordL>::iterator current;
        current = m_chordlists[abctrack].begin();
        int currentvelocity = -1;

        while ( current != m_chordlists[abctrack].end())
        {

            int wantedvelocity = int( (   ( ( current->velocity-127) * m_Mapping.m_volumecompress + m_Mapping.m_globalvolume+127) /9.0 -5.7)*0.77 + 1.5);
            if (wantedvelocity < 0) wantedvelocity = 0;
            if (wantedvelocity > 7) wantedvelocity = 7;

            if (current->is_rest)
            {
                m_ABCText << "z" << current->length << "/" << current->denominator << std::endl;
            }
            else
            {
                if (currentvelocity != wantedvelocity)
                {
                    m_ABCText << volumenames[wantedvelocity] << std::endl;
                    currentvelocity = wantedvelocity;
                }
                std::list<ChordL>::iterator next;
                m_ABCText << "[";
                for (std::list<int>::iterator npitch = current->npitches.begin(); npitch != current->npitches.end(); npitch++)
                {
                    m_ABCText << pitchnames[*npitch] << current->length << "/" << current->denominator;
                    next = current;
                    next++;
                    if (next != m_chordlists[abctrack].end())
                        for (std::list<int>::iterator nextcpitch = next->cpitches.begin(); nextcpitch != next->cpitches.end(); nextcpitch++)
                        {
                            if ( *npitch == *nextcpitch ) m_ABCText << "-";
                        }
                }
                for (std::list<int>::iterator cpitch = current->cpitches.begin(); cpitch != current->cpitches.end(); cpitch++)
                {
                    m_ABCText << pitchnames[*cpitch] << current->length << "/" << current->denominator;
                    next = current;
                    next++;
                    if (next != m_chordlists[abctrack].end())
                        for (std::list<int>::iterator nextcpitch = next->cpitches.begin(); nextcpitch != next->cpitches.end(); nextcpitch++)
                        {
                            if ( *cpitch == *nextcpitch ) m_ABCText << "-";
                        }
                }
                m_ABCText << "]" << std::endl;
            }


            current++;
        }
        m_ABCText << std::endl;
    }
}

void Brute::ExportABC(char * abcfilename)
{

    GenerateABC(); // first make sure we got the correct ABC

    std::ofstream myabcfile;
    myabcfile.open(abcfilename);

    myabcfile << m_ABCText.rdbuf();

    myabcfile.close();
}

// this goes over the quantized tones and sets the flags for tones to be selected or not for each abctrack/miditrack
void Brute::GenerateNoteSelection()
{

    int abctracks = static_cast<int> ( m_Mapping.m_instrumap.size());
    m_selected.resize(abctracks);
    #pragma omp parallel for
    for (int abctrack = 0; abctrack < abctracks; abctrack++)
    {
        int miditracks = m_Mapping.m_trackmap[abctrack].size();
        m_selected[abctrack].resize(miditracks);


        for (int miditrack = 0; miditrack < miditracks; miditrack++)
        {
            int thismiditrack = m_Mapping.m_trackmap[abctrack][miditrack];
            // get number of tones of this miditrack
            m_selected[abctrack][miditrack].resize( m_tonecounts[thismiditrack] );
            for (int event = 0; event < m_tonecounts[thismiditrack]; event++)
                m_selected[abctrack][miditrack][event]=true;

        }
    }


    // now we got the data structure reserved
    // #pragma omp parallel for
    for (int abctrack = 0; abctrack < abctracks; abctrack++)
    {
        int miditracks = m_Mapping.m_trackmap[abctrack].size();
        for (int miditrack = 0; miditrack < miditracks; miditrack++)
        {
            if (( m_Mapping.m_alternatemap[abctrack][miditrack] > 1) || (m_Mapping.m_splitvoicemap[abctrack][miditrack]>0))
            {
                // this track is alternated!
                int utrack = m_Mapping.m_trackmap[abctrack][miditrack];
                int ntones = m_tonecounts[utrack];
                int eventcounter = 0;
                int tonenumber = 0;
                double currenttime = 0;
                int thispart = 1;
                int alternateparts = m_Mapping.m_alternatemap[abctrack][miditrack];
                int alternatepart = m_Mapping.m_alternatepart[abctrack][miditrack];

                while ( tonenumber < ntones)
                {
                    // first take the tone and see if the starting time changed
                    if (( m_tonestarts[utrack][tonenumber] < currenttime   - 0.0000001 )
                            || (m_tonestarts[utrack][tonenumber] > currenttime + 0.0000001 ))
                    {
                        // time changed so increase the counter and take new time
                        eventcounter += 1;
                        currenttime = m_tonestarts[utrack][tonenumber];
                        thispart = 1;
                    }
                    else
                    {
                        // time didn't change
                        thispart++;
                    }

                    // see if this tone is picked
                    if (m_Mapping.m_alternatemap[abctrack][miditrack]>1)
                        if ( eventcounter % alternateparts != alternatepart )
                            m_selected[abctrack][miditrack][tonenumber] = false;

                    if (m_Mapping.m_splitvoicemap[abctrack][miditrack]>0)
                        if ( thispart != m_Mapping.m_splitvoicemap[abctrack][miditrack])
                            m_selected[abctrack][miditrack][tonenumber] = false;

                    // move a tone further
                    tonenumber++;
                }
            }
        }
    }
}
#endif
