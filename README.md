BruTE++

This is a follow up for the python based BruTE in C++. No external binaries are used anymore.
Libraries needed to compile: MidiFile, TinySoundFont and WxWidgets. 
Audio Preview is rendered directly by BruTE++ instead of intermediate Midi Files resulting in no issues with the number of tracks.


Current state: 

  still buggy ( regular crashes ) but basically implements the same functionality as BruTE: 
    - Midi loading
    - editing a text window for the arrangement
    - exporting an ABC as well as starting some Audio Preview using the registered program for WAV files in Windows.


