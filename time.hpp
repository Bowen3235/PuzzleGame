#ifndef time_hpp
#define time_hpp

#include "myTexture.hpp"

extern bool quit;
extern bool Propget[3];
extern int timeplus;
extern bool time_15;
extern int Count;
extern bool TimeUp;
extern int NoTime;

class Time
{
public:
    
    Time(int Total);
    void setTotalTime(int Total);
    
    void setTime(int M,int S);
    void set_dt(double i = 1);
    void count();
    
    char time[5];
    
private:
    int m = 0;
    int s = 0;
    int total = 0;
    int dt = 1000;
};

#endif /* time_hpp */
