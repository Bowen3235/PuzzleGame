#ifndef initialize_hpp
#define initialize_hpp

#include "myTexture.hpp"
#include "time.hpp"
#include "backgroundfunction.hpp"

extern const int Map_Width;
extern const int Map_Height;

extern const int Screen_Width;
extern const int Screen_Height;

extern SDL_Window* MainWindow;
extern SDL_Renderer* MainRenderer;
extern TTF_Font* gFont;

extern myTexture manTexture[2];
extern myTexture mapTexture;
extern myTexture barrierTexture[9];
extern myTexture timeTexture[2];
extern myTexture propTexture[3];
extern myTexture propBuff[3];
extern myTexture signTexture[6];

extern Time timer;

extern SDL_Color textColor;
extern Uint8 fade;

extern bool quit;
extern bool dead;
extern bool TimeUp;

extern bool Propexist[3];
extern bool Propfail[3];
extern bool Propget[3];
extern int StopTime[3];
extern int GetPropTime[3];
extern int Count;
extern int DeadTime;
extern int NoTime;
extern int times;//指定位置碰撞次數


bool Init();
bool loadMedia();
void Close();

#endif /* initialize_hpp */
