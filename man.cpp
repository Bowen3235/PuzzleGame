#include "man.hpp"

man::man()
{
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
    
    mCollider.w = Man_Width;
    mCollider.h = Man_Height;
}

void man::RandomDirectionPlus(int i)
{
    switch(i%4)
    {
        case 0: mVelY -= Man_Vel; break;
        case 1: mVelY += Man_Vel; break;
        case 2: mVelX -= Man_Vel; break;
        case 3: mVelX += Man_Vel; break;
            
    }
}

void man::RandomDirectionMinus(int i)
{
    switch(i%4)
    {
        case 0: mVelY += Man_Vel; break;
        case 1: mVelY -= Man_Vel; break;
        case 2: mVelX += Man_Vel; break;
        case 3: mVelX -= Man_Vel; break;
    }
}

void man::handleEvent( SDL_Event& e,int i)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: RandomDirectionPlus(i); break;
            case SDLK_DOWN: RandomDirectionPlus(i+1); break;
            case SDLK_LEFT: RandomDirectionPlus(i+2); break;
            case SDLK_RIGHT: RandomDirectionPlus(i+3); break;
        }
    }
    
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: RandomDirectionMinus(i); break;
            case SDLK_DOWN: RandomDirectionMinus(i+1); break;
            case SDLK_LEFT: RandomDirectionMinus(i+2); break;
            case SDLK_RIGHT: RandomDirectionMinus(i+3); break;
        }
    }
}

void man::move( SDL_Rect wall[28] )
{
    if(Count == 4)
    {
        mPosX += mVelX;
        mCollider.x = mPosX;
        mPosY += mVelY;
        mCollider.y = mPosY;
    }
    
    bool judge = false;
    //破關順序：總圖(20)->普通(8)->德田(25)->舊體(7)->保健中心(22)->足球場(0)->活大(21)->小福(5)->博理(24)->計中(17)
    for(int i=0;i<28;i++)
    {
        judge = checkCollision(wall[i]);
        
        if(judge)
        {
            if(i == 20 and (times == 0 or enter[0] == true))
            {
                if(mPosX<=3080)mPosX += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(1);
                if(times == 0){enter[times] = true;times++;}
            }
            if(i == 8 and (times == 1 or enter[1] == true))
            {
                if(mPosX>=1360)mPosX -= 5;
                if(mPosY<=960)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(2);
                if(times == 1){enter[times] = true;times++;}
            }
            if(i == 25 and (times == 2 or enter[2] == true))
            {
                if(mPosX>=3160)mPosX -= 5;
                if(mPosY<=840)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(3);
                if(times == 2){enter[times] = true;times++;}
            }
            if(i == 7 and (times == 3 or enter[3] == true))
            {
                if(mPosX>=1360)mPosX -= 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(4);
                if(times == 3){enter[times] = true;times++;}
            }
            if(i == 22 and (times == 4 or enter[4] == true))
            {
                if(mPosX<=3080)mPosX += 5;
                if(mPosY<=1720)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(5);
                if(times == 4){enter[times] = true;times++;}
            }
            if(i == 0 and (times == 5 or enter[5] == true))
            {
                if(mPosX<=1280)mPosX += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(6);
                if(times == 5){enter[times] = true;times++;}
            }
            if(i == 21 and (times == 6 or enter[6] == true))
            {
                if(mPosX<=3080)mPosX += 5;
                if(mPosY>=1040)mPosY -= 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(7);
                if(times == 6){enter[times] = true;times++;}
            }
            if(i == 5 and (times == 7 or enter[7] == true))
            {
                if(mPosX<=2160)mPosX += 5;
                if(mPosY<=960)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(8);
                if(times == 7){enter[times] = true;times++;}
            }
            if(i == 24 and (times == 8 or enter[8] == true))
            {
                if(mPosY<=840)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(9);
                if(times == 8){enter[times] = true;times++;}
            }
            if(i == 17 and (times == 9 or enter[9] == true))
            {
                if(mPosX<=2240)mPosX += 5;
                if(mPosY<=960)mPosY += 5;
                mVelX = 0;
                mVelY = 0;
                exWindow1(10);
                if(times == 9){enter[times] = true;times++;}
            }
            goto there;
        }
    }
    
there:
    if( ( mPosX < 0 ) || ( mPosX + Man_Width > Map_Width ) || judge )
    {
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    if( ( mPosY < 0 ) || ( mPosY + Man_Height > Map_Height ) || judge )
    {
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void man::render( int& camX, int& camY ,SDL_Rect* c)
{
    if(mVelX>=0)manTexture[0].render(mPosX - camX,mPosY - camY,c);
    else manTexture[1].render(mPosX-camX, mPosY-camY,c);
}

void man::set_dV(int vel)
{
    Man_Vel = vel;
}

void man::setMan(int x, int y, int vX, int vY)
{
    mPosX = x;
    mPosY = y;
    mVelX = vX;
    mVelY = vY;
}

bool man::checkCollision( SDL_Rect& a)const
{
    int leftA,rightA,topA,bottomA;
    
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    if(mCollider.y+mCollider.h<= topA )return false;
    if( mCollider.y >= bottomA )return false;
    if( mCollider.x+mCollider.w <= leftA )return false;
    if( mCollider.x >= rightA )return false;
    
    return true;
}

int man::getPosX()const
{
    return mPosX;
}

int man::getPosY()const
{
    return mPosY;
}
