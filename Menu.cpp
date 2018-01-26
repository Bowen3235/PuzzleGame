//
//  Menu.cpp
//  final project_demo
//
//  Created by nettoycrick on 12/12/2017.
//  Copyright © 2017 nettoycrick. All rights reserved.
//

#include "Menu.hpp"
#include "backgroundfunction.hpp"
#include <iostream>

enum options{
    Start,
    Teach,
    About,
    Leave
};

int Menu(){
    Uint32 t=0,pt=0;
    mymusic music("Resource/music/Yee.wav","music");
    mymusic punch( "Resource/music/PUNCH #4.wav","" ),
            reload( "Resource/music/RELOADING.wav" , "" );
    Mix_VolumeMusic(40);
    Mix_Volume( -1 , 90 );
    mytexture Menupic;
    mytexture selectpic;
    mytexture about;
    mytexture background;
    SDL_Rect aboutrect={50,50,860,440};
    mytexture text[4];
    SDL_Rect textpos[4],selecpos;
    SDL_Event move;
    int nowpos=0;
    
    music.play( -1 );
    
    text[Start].loadText("開始", 0 , 0 , 0 , 70);
    textpos[Start]={350,250,text[Start].getwidth(),text[Start].getheight()};
    
    text[Teach].loadText("教學", 0 , 0 , 0 , 70);
    textpos[Teach]={450+text[Start].getwidth(),250,text[Teach].getwidth(),text[Start].getheight()};
    
    text[About].loadText("關於", 0 , 0 , 0 , 70);
    textpos[About]={350,250+text[Start].getheight()+50
        ,text[Start].getwidth(),text[Start].getheight()};
    
    text[Leave].loadText("離開", 0 , 0 , 0 , 70);
    textpos[Leave]={450+text[Start].getwidth(),
        300+text[0].getheight(),text[Start].getwidth(),text[Start].getheight()};
    
    selectpic.loadFromfile("ReSource/select.png");
    selecpos=textpos[0];
    selecpos.y+=text[0].getheight()/2-30/2;
    selecpos.x-=text[0].getheight()-30;
    selecpos.w=text[0].getheight()-30;
    selecpos.h=text[0].getheight()-30;
    
    bool nextstage=false;
    Menupic.loadFromfile("ReSource/Menu.bmp");
    about.loadFromfile("ReSource/about.png");
    Menupic.render();
    for (int i=0;i<4;i++)
        text[i].render(NULL,&textpos[i]);
Back:
    while(!nextstage){
        while(SDL_PollEvent(&move)!=0 ){
                
            switch (move.key.keysym.sym) {
                    
                case SDLK_UP:
                    pt=SDL_GetTicks();
                    punch.changestate(false);
                    if(nowpos>1)
                        nowpos-=2;
                    break;
                case SDLK_DOWN:
                    pt=SDL_GetTicks();
                    punch.changestate(false);
                    if(nowpos<2)
                        nowpos+=2;
                    break;
                case SDLK_LEFT:
                    pt=SDL_GetTicks();
                    punch.changestate(false);
                    if(nowpos%2==1)
                        nowpos--;
                    break;
                case SDLK_RIGHT:
                    pt=SDL_GetTicks();
                    punch.changestate(false);
                    if(nowpos%2==0)
                        nowpos++;
                    break;
                case SDLK_RETURN:
                    reload.play(1);
                    nextstage=true;
                    break;
                default:
                    break;
            }
        
        }
        if(!punch.getstate() && pt - t > 150 ){
            punch.play(1);
            punch.changestate(true);
            t=SDL_GetTicks();
        }
        SDL_RenderClear( MainRenderer );
        Menupic.render(NULL,NULL);
        selecpos=textpos[nowpos];
        selecpos.y+=text[nowpos].getheight()/2-30/2;
        selecpos.x-=text[nowpos].getheight()-30;
        selecpos.w=text[nowpos].getheight()-30;
        selecpos.h=text[nowpos].getheight()-30;
        selectpic.render(NULL,&selecpos);
        for (int i=0;i<4;i++)
            text[i].render(NULL,&textpos[i]);
            SDL_RenderPresent(MainRenderer);
        }
    if(nowpos==2){
        while(nowpos==2){
            Menupic.render();
            about.render(NULL,&aboutrect);
            SDL_RenderPresent(MainRenderer);
            while(SDL_PollEvent(&move)!=0){
                if(move.key.keysym.sym==SDLK_b){
                    reload.play( 1 );
                    nextstage=false;
                    goto  Back;
                    }
            }
        }
        SDL_RenderClear( MainRenderer );
    }
    if( nowpos == Teach ){
        int preframe=0;
        int frame = 0;
        int TeachState=1;
        mytexture teach_1[3],teach_2[4];
        teach_1[0].loadFromfile("Resource/teach_1_1.png");
        teach_1[1].loadFromfile("Resource/teach_1_2.png");
        teach_1[2].loadFromfile("Resource/teach_1_3.png");
        while(nowpos==Teach){
            
            Menupic.render();
            
            if( TeachState == 1 ){
                teach_1[ (frame/50) %3 ].render( NULL,&aboutrect );
            }
            if( TeachState == 2 ){
                teach_2[ (frame/50) %4 ].render( NULL,&aboutrect );
            }
            
            SDL_RenderPresent(MainRenderer);
            while(SDL_PollEvent(&move)!=0){
                if( TeachState == 1 ){
                    if( move.key.keysym.sym ==SDLK_RIGHT ){
                        reload.play( 1 );
                        preframe=frame;
                        TeachState =2;
                        for(int i=0 ; i<3; i++){
                            teach_1[i].free();
                        }
                        teach_2[0].loadFromfile("Resource/teach_2_1.png");
                        teach_2[1].loadFromfile("Resource/teach_2_2.png");
                        teach_2[2].loadFromfile("Resource/teach_2_3.png");
                        teach_2[3].loadFromfile("Resource/teach_2_4.png");
                    }
                    
                    
                }
                if( TeachState ==2 && frame - preframe > 10 ){
                    if( move.key.keysym.sym ==SDLK_RIGHT ){
                        reload.play( 1 );
                        nowpos=0;
                        nextstage=false;
                        goto Back;
                    }
                }
                
            }
            frame++;
            if(frame>1000)
                frame=0;
        }
        SDL_RenderClear( MainRenderer );
        
    }
    fadeout(1,&Menupic);
    return nowpos;
}
