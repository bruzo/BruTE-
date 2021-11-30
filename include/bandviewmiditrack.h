#ifndef BANDVIEWMIDITRACK_H
#define BANDVIEWMIDITRACK_H


class BandViewMidiTrack
{
public:
    int range_l;
    int range_h;
    int volume;
    int miditrack;          // the id of the miditrack in the BruTE midi tracklist
    int midiinstrument;     // the numeric value of the original midi instrument
    int pitch;
    bool isdrum;
};

#endif
