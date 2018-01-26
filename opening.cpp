//
//  opening.cpp
//  final project_demo
//
//  Created by nettoycrick on 11/12/2017.
//  Copyright © 2017 nettoycrick. All rights reserved.
//
#include "opening.h"
#include "backgroundfunction.hpp"
#include <stdio.h>
void opening(){
    mymusic open("Resource/music/INCEPTION FOG HORN.wav","music");
    
    bool quit=false;
    SDL_Event e;
    open.play(2);
    Mix_VolumeMusic(50);
    while(!quit){
        while(SDL_PollEvent(&e)!=0)
            if(e.type==SDL_QUIT)
                quit=true;
        mytexture openingpic;
        openingpic.loadFromfile("ReSource/opening.bmp");
        openingpic.render(NULL,NULL);
        fadein(4,&openingpic);
        for(int i=0;i<1000;i++)
            SDL_Delay(1);
        fadeout(6,&openingpic);
        quit=true;
    }
}
