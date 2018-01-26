#include "game_2.hpp"

SDL_Rect manSpriteClips[4];

const int Map_Width = 3840;
const int Map_Height = 2160;

const int Screen_Width = 960;
const int Screen_Height = 540;


extern SDL_Renderer* MainRenderer;
TTF_Font* gFont = NULL;

SDL_Color textColor = {0,0,0,255};
Uint8 fade = 255;

myTexture manTexture[2];
myTexture mapTexture;
myTexture barrierTexture[9];
myTexture timeTexture[2];
myTexture propTexture[3];
myTexture propBuff[3];
myTexture signTexture[6];



Time timer(0);//總分鐘**********

SDL_Rect camera = { 0, 0, Screen_Width, Screen_Height };

bool quit = false;
bool dead = false;
bool TimeUp = false;

bool Propexist[3] = {false};
bool Propfail[3] = {false};
bool Propget[3] = {false};
int StopTime[3] = {0};
int GetPropTime[3] = {0};
int Count = 0;
int DeadTime = 0;
int NoTime = 0;
int times = 0;//指定位置碰撞次數
bool enter[10] = {false};

SDL_Event e;



int game_2(bool RandomKeyJudge,int dV,int barrier_v,double dt,int TotalTime,int Proptime)
{
    
    mymusic music("Resource/music/Kevin Macleod - The Builder.wav","music");
    mymusic din("Resource/music/DING.wav","");
    mymusic swoosh("Resource/music/SWOOSH #3.wav","");
    mymusic fail("Resource/music/FAIL.wav","");
    mymusic winmu("Resource/music/VICTORY.wav","");
    
    music.play( -1 );
    
    manSpriteClips[ 0 ].x =   0;
    manSpriteClips[ 0 ].y =   0;
    manSpriteClips[ 0 ].w =  40;
    manSpriteClips[ 0 ].h = 40;
    
    manSpriteClips[ 1 ].x =  40;
    manSpriteClips[ 1 ].y =   0;
    manSpriteClips[ 1 ].w =  40;
    manSpriteClips[ 1 ].h = 40;
    
    manSpriteClips[ 2 ].x = 80;
    manSpriteClips[ 2 ].y =   0;
    manSpriteClips[ 2 ].w =  40;
    manSpriteClips[ 2 ].h = 40;
    
    manSpriteClips[ 3 ].x = 120;
    manSpriteClips[ 3 ].y =   0;
    manSpriteClips[ 3 ].w =  40;
    manSpriteClips[ 3 ].h = 40;

    Init();
    loadMedia();
    srand(time(NULL));
    
    
    int RandomKey;
    if(RandomKeyJudge)RandomKey = rand();//按鍵隨機**********
    else RandomKey = 0;
    
    man dot;
    Barrier bike[8];
    Barrier car[2];
    Barrier people;
    Barrier bird[4];
    Barrier truck;
    Props* prop[3] = {NULL};
    
    stringstream timeText;
    
    SDL_Rect wall[28];
    wall[0] = {960,360,320,400};//足球場
    wall[1] = {0,0,1280,1280};//左上
    wall[2] = {0,1520,1280,200};//中間
    wall[3] = {0,1960,3840,200};//底
    wall[4] = {1280,0,2560,80};//頂
    wall[5] = {1720,520,440,440};//小福
    wall[6] = {1720,200,440,320};//醉月湖
    wall[7] = {1400,320,320,200};//舊體
    wall[8] = {1400,640,320,320};//普通
    wall[9] = {1400,200,760,760};//小福塊
    wall[10] = {1400,1080,320,200};//小福左下一
    wall[11] = {1400,1520,320,200};//小福左下二
    wall[12] = {1840,1080,320,200};//小福右下一
    wall[13] = {1840,1520,320,200};//小福右下二
    wall[14] = {2280,1080,320,200};//上
    wall[15] = {2280,1520,320,200};//下
    wall[16] = {2280,80,320,320};//計中左
    wall[17] = {2600,80,120,160};//計中
    wall[18] = {2720,80,360,320};//計中右
    wall[19] = {2280,520,800,440};//女九
    wall[20] = {2840,1200,240,400};//總圖
    wall[21] = {2600,1080,480,120};//活大
    wall[22] = {2600,1600,480,120};//保健中心
    wall[23] = {2600,1080,480,640};//總圖塊
    wall[24] = {3520,520,320,320};//博理
    wall[25] = {3200,520,320,320};//德田
    wall[26] = {3200,80,640,760};//右上
    wall[27] = {3200,960,680,1000};//右下
    
    dot.set_dV(dV);//*移動速度*/
    dot.setMan(0,1390,0,0);
    people.setBarrier(2280,960, 2, 2, 32, 40);
    people.setNumber(10);
    
    for(int i=0;i<4;i++)
    {
        bike[i].setBarrier(2520,1280+60*i,-(rand()%5+barrier_v),0,60,60);/*速度可調*/
        bike[i].setNumber(i);
    }
    
    for(int i=4;i<8;i++)
    {
        bike[i].setBarrier(3120,1720+60*(i-4),-(rand()%5+barrier_v),0,60,60);/*速度可調*/
        bike[i].setNumber(i);
    }
    
    car[0].setBarrier(1280,1840,0,-(rand()%5+barrier_v),60,120);/*速度可調*/
    car[0].setNumber(8);
    car[1].setBarrier(1340,80,0,rand()%5+barrier_v,60,120);/*速度可調*/
    car[1].setNumber(9);
    
    bird[0].setBarrier(1750, 1150, 1, 1, 40, 40);
    bird[0].setNumber(11);
    bird[1].setBarrier(2190, 1150, 1, 1, 40, 40);
    bird[1].setNumber(12);
    bird[2].setBarrier(1750, 1590, 1, 1, 40, 40);
    bird[2].setNumber(13);
    bird[3].setBarrier(2190, 1590, 1, 1, 40, 40);
    bird[3].setNumber(14);
    
    truck.setBarrier(1400, 110, rand()%5+barrier_v,1, 120, 60);/*速度可調*/
    truck.setNumber(15);
    
    timer.setTotalTime(TotalTime);
    timer.set_dt(dt);//時間倍速
    
    int myframe = 0;//***************************/
    
  
    
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT )quit = true;
            dot.handleEvent(e,RandomKey);
        }
        
        SDL_Rect* currentClip = &manSpriteClips[ myframe / 4 ];///
        
        SDL_SetRenderDrawColor( MainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( MainRenderer );
        mapTexture.render( 0, 0, &camera );
        
        timer.count();
        timeText.str( "" );
        timeText <<"Time:"<<timer.time;
        timeTexture[1].loadFromRenderedText( timeText.str().c_str(), textColor );
        
        for(int i=0;i<3;i++)
        {
            if(!Propexist[i] && StopTime[i]==0){
                if(prop[i]!=NULL){delete prop[i]; prop[i] = NULL;}
                Propget[i] = false;
                if(i==1)time_15 = false;
                prop[i] = new Props(60*(rand()%64),60*(rand()%36),60,60,i);
                for(int j = 0;j<28;j++){
                    Propfail[i] = prop[i]->shadow(wall[j]);
                    if(Propfail[i]){
                        din.play( 1 );
                        goto beenshadowed;
                    }
                }
            beenshadowed:        if(Propfail[i]){delete prop[i];prop[i] = NULL;}
                        else Propexist[i] = true;
            }
        }
        
        int temp=0;
        dot.move(wall);
        for(int i=0;i<8;i++)bike[i].move(dot,barrier_v);
        for(int i=0;i<2;i++)car[i].move(dot,barrier_v);
        for(int i=0;i<4;i++)bird[i].move(dot,barrier_v);
        people.move(dot,barrier_v);
        truck.move(dot,barrier_v);
        for(int i=0;i<8;i++)for(int j=0;j<2;j++)bike[i].Crossroad(car[j],barrier_v);
        for(int i=0;i<3;i++)
        {
            if(Propexist[i])prop[i]->get(dot);
            if(Propget[i]){
                StopTime[i]=SDL_GetTicks()/1000;
                if(StopTime[i]*dt >= Proptime+GetPropTime[i]*dt){
                    StopTime[i] = 0;}
                
            }//暫停時間
        }
        for(int i=0;i<3;i++){
            if(Propget[i]){
            if(prop[i]->fist){
                swoosh.play( 1 );
                prop[i]->fist=false;
            }}
        }
        
        camera.x = ( dot.getPosX() + man::Man_Width / 2 ) - Screen_Width / 2;
        camera.y = ( dot.getPosY() + man::Man_Height / 2 ) - Screen_Height / 2;
        if( camera.x < 0 )camera.x = 0;
        if( camera.y < 0 )camera.y = 0;
        if( camera.x > Map_Width - camera.w )camera.x = Map_Width - camera.w;
        if( camera.y > Map_Height - camera.h )camera.y = Map_Height - camera.h;
        
        for(int i=0;i<3;i++)if(Propexist[i])prop[i]->render(camera.x, camera.y);
        for(int i=0;i<8;i++)bike[i].render(camera.x, camera.y);
        for(int i=0;i<2;i++)car[i].render(camera.x, camera.y);
        for(int i=0;i<4;i++)bird[i].render(camera.x, camera.y);
        people.render(camera.x, camera.y,currentClip);
        truck.render(camera.x, camera.y);
        for(int i=0;i<2;i++)timeTexture[i].render(10*i,10*i);
        if(Propget[0]){propBuff[0].render(0, 40);}
        if(Propget[2]){propBuff[2].render(0, 80);}
        dot.render( camera.x, camera.y,currentClip);
        for(int i=0;i<4;i++)
        {
            if(fade!=0 and Count == i )
            {
                signTexture[i].fadeout();
                if(i != 3){
                    signTexture[i].render(camera.w/2-45, camera.h/4);
                    din.play( 1 );
                }
                if(i == 3){
                    signTexture[i].render(camera.w/4, camera.h/4);
                    din.play( 1 );
                }
            }
            else if(fade == 0 and Count <= 3){fade = 255;Count++;}
        }
        if(dead and fade != 0 )
        {
            Count = 5;
            signTexture[4].fadeout();
            signTexture[4].render(camera.w/4, camera.h/4);
            fail.play( 1 );
        }
        if(TimeUp and fade != 0)
        {
            Count = 5;
            signTexture[5].fadeout();
            signTexture[5].render(camera.w/4, camera.h/4);
            fail.play( 1 );
        }
        if(quit){
            mytexture winpic("Resource/win.jpeg");
            Mix_HaltMusic();
            winmu.play( 1 );
            cout<<"Win"<<endl;
            SDL_Rect winRext{50,50,Width-100,Height-100};
            winpic.render(NULL,&winRext);
            SDL_RenderPresent( MainRenderer );
            SDL_Delay(5000);
            close();
            return 0;
        }
        if(dead and SDL_GetTicks()/1000 == DeadTime+3)quit = true;
        if(TimeUp and SDL_GetTicks()/1000 == NoTime+3)quit = true;
        
        SDL_RenderPresent( MainRenderer );
        
        ++myframe;
        
        if( myframe / 4 >= 4 )
        {
            myframe = 0;
        }
    }
    
    
    Close();
    return 1;
}
