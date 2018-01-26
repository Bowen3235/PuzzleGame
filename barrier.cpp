#include "barrier.hpp"

Barrier::Barrier()
{
    mPosX = 0;
    mPosY = 0;
    
    mVelX = 0;
    mVelY = 0;
    
};

void Barrier::Reset(int barrier_v)
{
    if(mNumber<4)
    {
        mPosX = 2520;
        mPosY = 1280+60*mNumber;
        mVelX = -(rand()%5+barrier_v);
    }
    
    else if(mNumber<8)
    {
        mPosX = 3120;
        mPosY = 1720+60*(mNumber-4);
        mVelX = -(rand()%5+barrier_v);
    }
    
    else if(mNumber<9)
    {
        mPosX = 1280;
        mPosY = 1840;
        mVelY = -(rand()%5+barrier_v);
    }
    
    else if(mNumber<10)
    {
        mPosX = 1340;
        mPosY = 80;
        mVelY = rand()%5+barrier_v;
    }
    
    else if(mNumber == 15)
    {
        mPosX = 1400;
    }
}

void Barrier::move(man& man,int barrier_v)//**********
{
    
    if(!Propget[0] and Count == 4)
    {
        mPosX += mVelX;
        mPosY += mVelY;
        mCollider.x = mPosX;
        mCollider.y = mPosY;
    
        if( mPosX+mWid<camera.x and mNumber<8)Reset(barrier_v);
        if( mPosY+mHei<camera.y and mNumber==8)Reset(barrier_v);
        if( mPosY+mHei<200 and mNumber==8)Reset(barrier_v);
        if( mPosY>camera.y+Screen_Height and mNumber==9)Reset(barrier_v);
        if( mPosY>1840 and mNumber==9)Reset(barrier_v);
        if(mNumber==10)
        {
            if(mCollider.y+mCollider.h>=1080 or mCollider.y<=960)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=3080 or mCollider.x<=1400 )mVelX = -mVelX;
        }
        if(mNumber==11)
        {
            if(mCollider.y+mCollider.h>=1280 or mCollider.y<=1080)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=1840 or mCollider.x<=1720 )mVelX = -mVelX;
        }
        if(mNumber==12)
        {
            if(mCollider.y+mCollider.h>=1280 or mCollider.y<=1080)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=2280 or mCollider.x<=2160 )mVelX = -mVelX;
        }
        if(mNumber==13)
        {
            if(mCollider.y+mCollider.h>=1720 or mCollider.y<=1520)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=1840 or mCollider.x<=1720 )mVelX = -mVelX;
        }
        if(mNumber==14)
        {
            if(mCollider.y+mCollider.h>=1720 or mCollider.y<=1520)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=2280 or mCollider.x<=2160 )mVelX = -mVelX;
        }
        if(mNumber==15)
        {
            if(mCollider.y+mCollider.h>=200 or mCollider.y<=80)mVelY = -mVelY;
            if( mCollider.x+mCollider.w>=2160 or mCollider.x<=1400 )Reset(barrier_v);
        }
    }
    
     if(checkCollision(man) and !Propget[2] and !dead)
     {
         
         Mix_HaltMusic();
         
         dead = true;
         DeadTime = SDL_GetTicks()/1000;
     }
};

void Barrier::render(int& camX, int& camY,SDL_Rect* c)
{
    if(mNumber < 8)barrierTexture[0].render(mPosX - camX, mPosY - camY);
    else if(mNumber == 8)barrierTexture[1].render(mPosX - camX, mPosY - camY);
    else if(mNumber == 9)barrierTexture[2].render(mPosX - camX, mPosY - camY);
    else if(mNumber == 10)
    {
        if(mVelX<=0)barrierTexture[3].render(mPosX - camX, mPosY - camY,c);
        if(mVelX>=0)barrierTexture[4].render(mPosX - camX, mPosY - camY,c);
    }
    else if(mNumber<15)
    {
        if(mVelX<=0)barrierTexture[6].render(mPosX - camX, mPosY - camY);
        if(mVelX>=0)barrierTexture[7].render(mPosX - camX, mPosY - camY);
    }
    else barrierTexture[8].render(mPosX - camX , mPosY - camY);
    
};

void Barrier::set_dV(int vel)
{
    Barrier_Vel = vel;
};

void Barrier::setBarrier(int x, int y, int vX, int vY,int W,int H)
{
    mPosX = x;
    mPosY = y;
    mVelX = vX;
    mVelY = vY;
    mWid = W;
    mHei = H;
    mCollider.w = mWid;
    mCollider.h = mHei;
};

void Barrier::setNumber(int i)
{
    mNumber = i;
};

void Barrier::Crossroad(Barrier& car,int barrier_v)//*************
{   if(mNumber<4)
    {
        if(car.mPosY>1160 and car.mPosY<1520 and mPosX>car.mPosX+car.mCollider.w and mPosX<car.mPosX+car.mCollider.w+80)
        {
            mPosX-=mVelX;
            mCollider.x = mPosX;
        }
    }
    else
    {
        if(car.mPosY>1600 and car.mPosY<1960 and mPosX>car.mPosX+car.mCollider.w and mPosX<car.mPosX+car.mCollider.w+80)
        {
            mPosX-=mVelX;
            mCollider.x = mPosX;
        }
    }
    int leftA,rightA,topA,bottomA;
    bool dead = true;
    
    leftA = car.mCollider.x;
    rightA = car.mCollider.x + car.mCollider.w;
    topA = car.mCollider.y;
    bottomA = car.mCollider.y + car.mCollider.h;
    
    if(mCollider.y+mCollider.h<= topA )dead = false;
    if( mCollider.y >= bottomA )dead = false;
    if( mCollider.x+mCollider.w <= leftA )dead = false;
    if( mCollider.x >= rightA )dead = false;
    if(dead == true)
    {
        barrierTexture[5].render(mCollider.x-camera.x,mCollider.y-camera.y);
        Reset(barrier_v);
    }
};

bool Barrier::checkCollision(man& man)const
{
    int leftA,rightA,topA,bottomA;
    
    leftA = man.mCollider.x;
    rightA = man.mCollider.x + man.mCollider.w;
    topA = man.mCollider.y;
    bottomA = man.mCollider.y + man.mCollider.h;
    
    if(mCollider.y+mCollider.h<= topA )return false;
    if( mCollider.y >= bottomA )return false;
    if( mCollider.x+mCollider.w <= leftA )return false;
    if( mCollider.x >= rightA )return false;
    
    return true;
};

int Barrier::getPosX()const
{
    return mPosX;
}

int Barrier::getPosY()const
{
    return mPosY;
}
