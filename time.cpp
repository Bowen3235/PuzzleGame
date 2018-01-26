#include "time.hpp"

using namespace std;

extern myTexture gTextTexture;
extern TTF_Font *gFont;
extern SDL_Color textColor;
int timeplus = 0;
bool time_15 = false;

Time::Time(int Total)
{
    total = Total;
    m = Total;
    time[0] = '0'+m/10;
    time[1] = '0'+m%10;
    time[2] = ':';
    time[3] = '0'+s/10;
    time[4] = '0'+s%10;
}

void Time::setTotalTime(int Total)
{
    total = Total;
    m = Total;
    s = 0;
    time[0] = '0'+m/10;
    time[1] = '0'+m%10;
    time[2] = ':';
    time[3] = '0'+s/10;
    time[4] = '0'+s%10;
}

void Time::setTime(int M,int S)
{
    m = M;
    s = S;
    time[0] = '0'+m/10;
    time[1] = '0'+m%10;
    time[2] = ':';
    time[3] = '0'+s/10;
    time[4] = '0'+s%10;
}

void Time::set_dt(double i)
{
    dt /= i;
}

void Time::count()
{
    if(Count == 4)
    {
        s=(total*60-SDL_GetTicks()/dt+15*timeplus+Count*1000/dt)%60;
        m=(total*60-SDL_GetTicks()/dt+15*timeplus+Count*1000/dt)/60;
        if(Propget[1] and !time_15){timeplus++;time_15 = true;}
    
        setTime(m,s);
    
        if(m == 0 and s<=10)textColor = {255,0,0,0};//紅字
        if(m == 0 and s==0){NoTime = SDL_GetTicks()/1000;TimeUp = true;}
        
    }
}
