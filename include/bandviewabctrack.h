#ifndef BANDVIEWABCTRACK_H_INCLUDED
#define BANDVIEWABCTRACK_H_INCLUDED

#include "bandviewmiditrack.h"

class BandViewABCTrack
{
public:
    int instrument;
    int x;
    int y;
    int polyphony = 6;
    int duration_min = 2;
    int duration_max = 0;
   // std::vector<int> miditracks = {};
    std::vector<BandViewMidiTrack> miditrackinfo = {};
};

#endif // BANDVIEWABCTRACK_H_INCLUDED
