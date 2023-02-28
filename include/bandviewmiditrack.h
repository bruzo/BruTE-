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
    int delay=0;

    bool isdrum=false;
    bool isempty=false;

    int alternateparts=1;
    int alternatemypart=1;
    int split = 0;
};

#endif
