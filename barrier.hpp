#ifndef barrier_hpp
#define barrier_hpp

#include "man.hpp"

using namespace std;

extern const int Screen_Width;
extern const int Screen_Height;
extern myTexture barrierTexture[9];
extern bool quit;
extern bool Propget[3];
extern bool dead;
extern SDL_Rect camera;
extern int Count;
extern int DeadTime;

class Barrier
{
    friend class man;
    
public:
    
    Barrier();
    
    void move(man& man,int barrier_v);
    void render(int& camX,int& camY,SDL_Rect* c=NULL);
    void set_dV(int vel);
    void setBarrier(int x,int y,int vX,int vY,int W,int H);
    void setNumber(int i);
    void Reset(int barrier_v);
    void Crossroad(Barrier& car,int barrier_v);
    
    bool checkCollision(man& man)const;
    
    int getPosX()const;
    int getPosY()const;
    
private:
    
    int Barrier_Vel;
    int mPosX,mPosY;
    int mVelX,mVelY;
    int mWid,mHei;
    int mNumber;
    
    SDL_Rect mCollider;
};

#endif /* bike_hpp */
