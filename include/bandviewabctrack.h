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
    int polydirection = 0;  // 0 is top, 1 is bottom
    int duration_min = 2;
    int duration_max = 0;
   // std::vector<int> miditracks = {};
    std::vector<BandViewMidiTrack> miditrackinfo = {};
    bool muted = false;
};

#endif // BANDVIEWABCTRACK_H_INCLUDED
