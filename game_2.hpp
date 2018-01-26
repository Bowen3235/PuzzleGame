#ifndef game_2_hpp
#define game_2_hpp

#include "initialize.hpp"
#include "myTexture.hpp"
#include "man.hpp"
#include "barrier.hpp"
#include "exWindow.hpp"
#include "time.hpp"
#include "props.hpp"
#include "backgroundfunction.hpp"

using namespace std;

extern const int Map_Width ;
extern const int Map_Height ;

extern const int Screen_Width ;
extern const int Screen_Height ;

extern SDL_Window* MainWindow ;
extern SDL_Renderer* MainRenderer ;
extern TTF_Font* gFont ;
extern SDL_Color textColor ;

extern myTexture manTexture[2];
extern myTexture mapTexture;
extern myTexture barrierTexture[9];
extern myTexture timeTexture[2];
extern myTexture propTexture[3];
extern Time timer;


extern SDL_Rect camera ;
extern Uint8 fade;

extern bool quit ;
extern bool Propexist[3] ;
extern bool Propfail[3] ;
extern bool Propget[3] ;
extern int StopTime[3] ;
extern int GetPropTime[3] ;
extern int Count;
extern int DeadTime;
extern int NoTime;
extern int times;//指定位置碰撞次數

extern SDL_Event e;

int game_2(bool RandomKeyJudge,int dV,int barrier_v,double dt,int TotalTime,int Proptime);

#endif /* game_2_hpp */
