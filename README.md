BruTE++

This is a follow up for the python based BruTE in C++. No external binaries are used anymore.
Libraries needed to compile: MidiFile, WxWidgets and OpenAL. 
Audio Preview is played via OpenAL like Lotro does, should provide very similar sound to the game.

Building under windows requires -D win32 to turn on specific includes for windows, as well as an implementation of fmemopen.
Building under linux requires installing development packages of your flavor of wxWidgets (GTK, ...) and the OpenAL library.

The program has been tested on Windows10 as a 64+32bit build and Linux/arm-hf (32-bit) and should compile without warnings. 

Current state: 

a bit buggy ( sometimes crashed ) but basically implements the same functionality as BruTE: 
    - Midi loading, ABC exporting
    - editing a text window for the arrangement
    - Band View for graphical arrangement
    - ...
 
ABC files generated with this Version can also be dropped on the Bandview for playback only.
    
Still to come (hopefully): Humanization, easier Drum Sample handling

