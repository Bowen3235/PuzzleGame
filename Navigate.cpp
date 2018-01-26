//
//  Navigate.cpp
//  final project_demo
//
//  Created by nettoycrick on 2018/1/8.
//  Copyright © 2018年 nettoycrick. All rights reserved.
//

#include "Navigate.hpp"

std::string redirection ( int Achieve , Uint32 passedTime ){
    enum{
        State_init,
        State_item,
        State_QInit,
        State_Q1,
        State_Q2,
        State_Q3,
        State_Thanks
    };
    
    mymusic music("Resource/music/Yee.wav","music");
    mymusic punch( "Resource/music/PUNCH #4.wav","" ),
    reload( "Resource/music/RELOADING.wav" , "" );
    
    Uint32 t=0,pt=0;
    int selecnum=1;
    mytexture inter("Resource/inter_1.png");
    mytexture selec("Resource/select_dot.png");
    std::stringstream result;
    
    SDL_RenderClear(MainRenderer);
    SDL_Rect SelecRect{345,225,30,30};
    
    inter.render(NULL,NULL);
    
    SDL_Event e;
    
    bool quit= false;
    int State=0;
    
    
    music.play( -1 );
    
    
    while( !quit ){
        while( SDL_PollEvent( &e ) != 0 ){
            t=SDL_GetTicks();
            if( e.key.keysym.sym==SDLK_RETURN && t-pt> 700 ){
                reload.play( 1 );
                if( State<=State_Q3 && State >= State_Q1  ){
                    if( State == State_Q1 )
                        result<<5+Achieve+selecnum;
                    else if( State == State_Q2 )
                        result<<2-Achieve+selecnum;
                    else if( State == State_Q3 )
                        result<<Achieve+selecnum;
                }
                pt=SDL_GetTicks();
                State++;
                switch (State) {
                    case 1:
                        if( Achieve == 1 ){
                            inter.loadFromfile("Resource/inter_item_1.png");
                        }
                        else if( Achieve == 2 ){
                            inter.loadFromfile("Resource/inter_item_2.png");
                        }
                        else if( Achieve == 0 ){
                            inter.loadFromfile("Resource/inter_item_0.png");
                        }
                        break;
                    case 2:
                        inter.loadFromfile("Resource/inter_2.png");
                        break;
                    case 3:
                        inter.loadFromfile("Resource/inter_q1.png");
                        break;
                    case 4:
                        inter.loadFromfile("Resource/inter_q2.png");
                        break;
                    case 5:
                        inter.loadFromfile("Resource/inter_q3.png");
                        break;
                    case 6:
                        inter.loadFromfile("Resource/inter_thanks.png");
                        break;
                    default:
                        break;
                }
            }
            if( State<=State_Q3 && State >= State_Q1 ){
                t=SDL_GetTicks();
                if( e.key.keysym.sym == SDLK_DOWN && selecnum < 3 && t-pt > 200 ){
                    punch.play( 1 );
                    selecnum++;
                    pt=SDL_GetTicks();
                }
                else if( e.key.keysym.sym == SDLK_UP && selecnum > 1 && t-pt > 200 ){
                    punch.play( 1 );
                    selecnum--;
                    pt=SDL_GetTicks();
                }
                switch ( selecnum ) {
                    case 1:
                        SelecRect.y=245;
                        break;
                    case 2:
                        SelecRect.y=325;
                        break;
                    case 3:
                        SelecRect.y=405;
                        break;
                    default:
                        break;
                }
                
                
            }
            
        }
        
        SDL_RenderClear(MainRenderer);
        inter.render(NULL,NULL);
        if( State<=State_Q3 && State >= State_Q1 ){
            selec.render(NULL,&SelecRect);}
        
        SDL_RenderPresent(MainRenderer);
        if( State > 6 ){
            Mix_HaltMusic();
            quit=true;
        }
        
    }
    
    
    
    
    
    return result.str();
}


