#ifndef ABCHT_H
#define ABCHT_H

// Class to handle everything about the input of ABC Files: loading / parsing and turning it into playable information for the audioplayer

#include<vector>
#include<list>
#include<string>

#include "brutedefinitions.h"



class ABCHeaderT
{
public:
    void SetStereoPosition(int pos);
    int GetStereoPosition();
    void SetDepthPosition(int pos);
    int GetDepthPosition();
    void SetID(int id);
    int GetID();
    void SetSpeed(int speed);
    int GetSpeed();
    void SetUnitLength(double unit);
    double GetUnitLength();
    void SetX(int x);
    int GetX();
    void SetInstrument(int i);
    int GetInstrument();

    void ParseLine(std::string line);
    double GetBeatsToSeconds();

private:
    int m_StereoPosition = 0;
    int m_DepthPosition = 300;
    int m_ID = 0;
    int m_Speed = 125;
    double m_UnitLength = 1.0/8.0;
    double m_Measure = 1.0;
    int m_Xnumber;
    int m_Instrument=0;
};

double ABCHeaderT::GetBeatsToSeconds()
{
    return 60.0/m_Speed * m_UnitLength / 0.25 / m_Measure ;  // probably only correct for BruTE tunes ...
}

void ABCHeaderT::SetInstrument(int i)
{
    m_Instrument = i;
}

int ABCHeaderT::GetInstrument()
{
    return m_Instrument;
}

void ABCHeaderT::SetStereoPosition(int pos)
{
    m_StereoPosition = pos;
}

int ABCHeaderT::GetStereoPosition()
{
    return m_StereoPosition;
}

void ABCHeaderT::SetDepthPosition(int pos)
{
    m_DepthPosition = pos;
}

int ABCHeaderT::GetDepthPosition()
{
    return m_DepthPosition;
}

void ABCHeaderT::SetID(int id)
{
    m_ID = id;
}

int ABCHeaderT::GetID()
{
    return m_ID;
}

void ABCHeaderT::SetSpeed(int speed)
{
    m_Speed = speed;
}

int ABCHeaderT::GetSpeed()
{
    return m_Speed;
}

void ABCHeaderT::SetUnitLength(double unit)
{
    m_UnitLength = unit;
}
double ABCHeaderT::GetUnitLength()
{
    return m_UnitLength;
}

void ABCHeaderT::SetX(int x)
{
    m_Xnumber = x;
}
int ABCHeaderT::GetX()
{
    return m_Xnumber;
}

void ABCHeaderT::ParseLine(std::string line)
{
    if (line[1] == ':')
    {
        // X: field
        if (line[0]=='X')
        {
            try {
                m_Xnumber = std::stoi(line.substr(2));
            }
            catch (const std::invalid_argument& ia)
            {
               m_Xnumber = 0;
            } catch (const std::out_of_range& oor)
            {
               m_Xnumber = 0;
            }
        }

        // Q: field
        if (line[0]=='Q')
        {
            size_t j = 2;
            for (size_t i = 0; i < line.size(); i++) if (line[i]=='=') j = i;
            try {
                m_Speed = std::stoi(line.substr(j));
            }
            catch (const std::invalid_argument& ia)
            {
               m_Speed = 120;
            } catch (const std::out_of_range& oor)
            {
               m_Speed = 120;
            }
        }
        // L: field
        if (line[0]=='L')
        {
            auto factors = split(line.substr(2),'/');
            double unit = 1.0;
            if (factors.size()> 0)
            {
               try
               {
                   unit = unit * std::stoi(factors[0]);
               }
               catch (const std::invalid_argument& ia){}
               catch (const std::out_of_range& oor){}
            }
            if (factors.size()>1)
            {
               try
               {
                   unit = unit / std::stoi(factors[1]);
               }
               catch (const std::invalid_argument& ia){}
               catch (const std::out_of_range& oor){}
            }
            m_UnitLength = unit;
           // std::cout << "Unit " << m_UnitLength << std::endl;
        }

        // see if we can find stereo positions in here
        if (line[0]=='Z')
        {
           auto arguments = split(line.substr(2),' ');
           int one = 0;
           int two = 0;
           int three = 0;
           bool failure = false;

           // the BruTE Z line has at least 4 entries, so only try this if it's like this
           if (arguments.size() > 3)
           {
               try
               {
                   three = std::stoi(arguments.back());
               }
               catch (const std::invalid_argument& ia){ failure = true;}
               catch (const std::out_of_range& oor){failure = true;}

               if (!failure)
               {
                   // we have a number in the end!
                   try
                   {
                      two = std::stoi( arguments[ arguments.size()-2]);
                   }
                   catch (const std::invalid_argument& ia){ failure = true;}
                   catch (const std::out_of_range& oor){failure = true;}

                   if (!failure)
                   {
                       // there was actually two numbers in the end of the line
                       try
                       {
                           one = std::stoi( arguments[arguments.size()-3]);
                       }
                       catch (const std::invalid_argument& ia){ failure = true;}
                       catch (const std::out_of_range& oor){failure = true;}
                       if (!failure)
                       {
                           // we got 3 numbers!!!
                           m_StereoPosition = one;
                           m_DepthPosition = two;
                           m_ID = three;
                       }
                       else
                       {
                           // well .. we got 2 numbers .. but not a third, lets assume final is stereo and prefinal is Depth
                           m_StereoPosition = three;
                           m_DepthPosition = two;
                           m_ID = -1;
                       }
                   }
                   else
                   {
                       // seems we only had one number in the end, lets treat that as stereo panning
                       two = 0;
                       m_StereoPosition = static_cast<int>((three - 64.0)/64*50) ;
                       m_DepthPosition = 300;
                       m_ID = -1;
                   }

               }
               else   // last is not a number, so we don't get anything from the Z-line
               {
                   m_StereoPosition = 0;
                   m_DepthPosition = 300;
                   m_ID = -1;
               }
           }
           else
           {
               // this is not enough arguments anyway
               m_StereoPosition = 0;
               m_DepthPosition = 300;
               m_ID = -1;
           }
         //  std::cout << m_StereoPosition << "  " << m_DepthPosition << "  " << m_ID << std::endl;
        }

        // see if we can find stereo positions in here
        if (line[0]=='T')
        {
            // this is the instrument line!
            try{
               m_Instrument = GetABCInstrumentFromTLine(line);
            }
            catch (const std::invalid_argument& ia){ m_Instrument = 0;}
            catch (const std::out_of_range& oor){m_Instrument = 0;}
        }

                // L: field
        if (line[0]=='M')
        {
            auto factors = split(line.substr(2),'/');
            double unit = 1.0;
            if (factors.size()> 0)
            {
               try
               {
                   unit = unit * std::stoi(factors[0]);
               }
               catch (const std::invalid_argument& ia){}
               catch (const std::out_of_range& oor){}
            }
            if (factors.size()>1)
            {
               try
               {
                   unit = unit / std::stoi(factors[1]);
               }
               catch (const std::invalid_argument& ia){}
               catch (const std::out_of_range& oor){}
            }
            m_Measure = unit;
            //std::cout << "Unit " << m_UnitLength << std::endl;
        }

    }
}

#endif // ABCHT
