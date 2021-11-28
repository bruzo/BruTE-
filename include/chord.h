#ifndef CHORDL_H
#define CHORDL_H

#include<vector>
#include<list>
#include<string>

class ChordL
{
public:

    std::list<int> cpitches; // continued pitches
    std::list<int> npitches; // newly starting pitches
    int velocity;            // overall velocity
    double duration;         // duration of this chord
    double missmatch;        // dominating tone missmatch in this slot
    bool is_rest;          // is this just a break?
    std::string durationstring; // this is string value for this duration
    std::string ChordName;  // this is the full text line for the chord
    int length;
    int denominator;
    double original_starting_time; // just to know when this was
};


#endif
