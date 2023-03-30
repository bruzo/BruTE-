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
    int getX();

    void ParseLine(std::string line);

private:
    int m_StereoPosition = 0;
    int m_DepthPosition = 0;
    int m_ID = 0;
    int m_Speed = 120;
    double m_UnitLength = 1.0/8.0;
    int m_Xnumber;
};

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
int ABCHeaderT::getX()
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
            try {
                m_Speed = std::stoi(line.substr(2));
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
        }

        // see if we can find stereo positions in here
        if (line[0]=='Z')
        {
           auto arguments = split(line.substr(2),' ');

        }
    }

}

#endif // ABCHT
