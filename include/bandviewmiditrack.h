#ifndef BANDVIEWMIDITRACK_H
#define BANDVIEWMIDITRACK_H


class BandViewMidiTrack
{
public:
    int range_l = 0;
    int range_h = 36;
    int volume =0;
    int miditrack;          // the id of the miditrack in the BruTE midi tracklist
    int midiinstrument;     // the numeric value of the original midi instrument
    int pitch=0;
    float delay=0;
    int drummapping = 0;

    bool isdrum=false;
    bool isempty=false;

    int alternateparts=1;
    int alternatemypart=1;
    int split = 0;

    bool haspitchbends = false;

    int pitchbendqduration = 0;
    int pitchbendmethod = 0;
    float triller = 0;

    int durationsplitlength = 0;
    int durationsplitpart = 0;

    int directmapping = -1;
    int drumtone = -1;

    std::vector < bool > * samples;
};

#endif
