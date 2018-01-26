#include "props.hpp"

Props::Props(int x,int y,int w,int h,int n)
{
    pX = x;
    pY = y;
    pW = w;
    pH = h;
    pNumber = n;
}

void Props::get(man& man)
{
    
    Propexist[pNumber] = !Checkcollision(man);
    if(Checkcollision(man)){
        mymusic din("Resource/music/DING.wav","");
        Propget[pNumber] = true;
        din.play(1);
        fist=true;
    }
    GetPropTime[pNumber] = SDL_GetTicks()/1000;
}

void Props::render(int &camX, int &camY)
{
    propTexture[pNumber].render(pX-camX, pY-camY);
}

bool Props::Checkcollision(man& man)
{
    int leftA,rightA,topA,bottomA;
    
    leftA = man.mCollider.x;
    rightA = man.mCollider.x + man.mCollider.w;
    topA = man.mCollider.y;
    bottomA = man.mCollider.y + man.mCollider.h;
    
    if(pY+pH<= topA )return false;
    if( pY >= bottomA )return false;
    if( pX+pW <= leftA )return false;
    if( pX >= rightA )return false;
    
    return true;
}

bool Props::shadow(SDL_Rect& wall)
{
    int leftA,rightA,topA,bottomA;
    
    leftA = wall.x;
    rightA = wall.x + wall.w;
    topA = wall.y;
    bottomA = wall.y + wall.h;
    
    if(pY+pH<= topA )return false;
    if( pY >= bottomA )return false;
    if( pX+pW <= leftA )return false;
    if( pX >= rightA )return false;
    
    return true;
}
