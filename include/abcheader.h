#ifndef ABCHEADER_H_INCLUDED
#define ABCHEADER_H_INCLUDED

#include <string>

class ABCHeader
{
public:
    std::string SongName = "<insert title>";
    int speedup = 0;
    int globalpitch = 0;
    int globalvolume = 0;
    std::string Transcriber = "Himbeertony";
};

#endif // ABCHEADER_H_INCLUDED
