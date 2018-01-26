#ifndef man_hpp
#define man_hpp

#include "myTexture.hpp"
#include "exWindow.hpp"

using namespace std;

extern const int Map_Width;
extern const int Map_Height;
extern myTexture manTexture[2];
extern int times;
extern bool enter[10];
extern int Count;

class man
{
    friend class Barrier;
    friend class Props;
    
public:
    
    man();
    
    static const int Man_Width = 40;
    static const int Man_Height = 40;
    
    void RandomDirectionPlus(int i);
    void RandomDirectionMinus(int i);
    void handleEvent(SDL_Event& e,int i=0);
    void move(SDL_Rect wall[28]);
    void render(int& camX,int& camY,SDL_Rect* c=NULL);
    void set_dV(int vel);
    void setMan(int x,int y,int vX,int vY);
    
    bool checkCollision(SDL_Rect& a)const;
    
    int getPosX()const;
    int getPosY()const;
    
private:
    
    int Man_Vel;
    int mPosX,mPosY;
    int mVelX,mVelY;
    
    SDL_Rect mCollider;
};

#endif /* man_hpp */
