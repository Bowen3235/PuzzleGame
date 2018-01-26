//
//  main.cpp
//  final project_demo
//
//  Created by nettoycrick on 11/12/2017.
//  Copyright © 2017 nettoycrick. All rights reserved.
//

#include <iostream>
#include "opening.h"
#include "backgroundfunction.hpp"
#include "Menu.hpp"
#include "Stage_1.hpp"
#include "game_2.hpp"
#include "Navigate.hpp"

enum{
    Go_continue,
    Go_Readfile,
    Go_Menu,
    Go_Close
};

extern SDL_Window* MainWindow;
extern SDL_Renderer* MainRenderer;

int main(int argc, const char * argv[]) {
    int nextstate=Go_Menu;
    int Achieve=0;
    Uint32 t=0;
    string the="";
    int para[3]={0};
    
    
    init();
    
    opening();
    
    while(nextstate==Go_Menu)
        nextstate=Menu();
     
    if(nextstate==Go_Close){
        close();
        return 0;
    }
    
    t=SDL_GetTicks();
    Achieve = stage_1();
    t=SDL_GetTicks()-t;
    
    
    
    the=redirection( Achieve , t );
    
    for( int i=0 ; i<3 ; i++ ){
        para[i]=the[i]-'0';
        if( i == 2 )
            para[i]+=8;
        printf("%d",para[i]);
    }
    if(para[1]>1)
        para[1]-=1;
    
    
    nextstate=game_2(false, para[0], para[1] , 1, para[2] , 10);
    //隨機按鍵,人物速度,障礙物速度,時間倍速,總時間,道具生成時間(效果持續時間)
    //破關順序：總圖->普通->德田->舊體->保健中心->足球場->活大->小福->博理->計中
    
    close();
    return 0;
}

