#ifndef ABC_H
#define ABC_H

// Class to handle everything about the input of ABC Files: loading / parsing and turning it into playable information for the audioplayer

#include<vector>
#include<list>
#include<string>

class ABCInput
{
public:

   void LoadABC(std::stringstream * abctext);
   void LoadABC(std::string filename);



};

void ABCInput::LoadABC(std::stringstream * abctext)
{

}

void ABCInput::LoadABC(std::string filename)
{

}


#endif
