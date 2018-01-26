//
//  Stage_1.cpp
//  final project_demo
//
//  Created by nettoycrick on 2017/12/28.
//  Copyright © 2017年 nettoycrick. All rights reserved.
//

#include "Stage_1.hpp"

mytexture Background;
item Bed,Door,LDrawer,RDrawer,QCTip;

int RE=0;



int stage_1(){
    
    mymusic found("Resource/music/CARTOON POP.wav","");
    mymusic click("Resource/music/mouse clicks Sound Effect.wav","" );
    mymusic herewego("Resource/music/MARIO HERE WE GO.wav","");
    mymusic err("Resource/music/HA HA (NELSON).wav","");
    Mix_Volume( -1 , 100 );
    herewego.play(1);
    
    mymusic music("Resource/music/ILLUMINATI.wav","music");
    
    
    Background.loadFromfile( "Resource/Room.png" );
    Background.render();
    
    bool quit=false;
    SDL_Event e;
    
    ItemCollum mCollum;
    
    SDL_Rect tempP={ 740 , 360 , 220 , 180 },
    tempC={ tempP.x*2 , tempP.y*2 , tempP.w*2 , tempP.h*2 };
    Bed.loadmedia( "Resource/Roomopen.png" , &tempC , &tempP , "y" );
    
    tempP={ 145 , 185 , 145 , 355 };
    tempC={ tempP.x*2 , tempP.y*2 , tempP.w*2 , tempP.h*2 };
    Door.loadmedia( Bed.GiveTex( ) , &tempC ,&tempP , "y" );
    
    tempP={ 290 , 440 , 105 , 55 };
    tempC={ tempP.x*2 , tempP.y*2 , tempP.w*2 , tempP.h*2 };
    LDrawer.loadmedia( Bed.GiveTex( ) , &tempC ,&tempP , "y" );
    
    tempP={ 500 , 410 , 110 , 90 };
    tempC={ tempP.x*2 , tempP.y*2 , tempP.w*2 , tempP.h*2 };
    RDrawer.loadmedia( Bed.GiveTex( ) , &tempC ,&tempP , "y" );
    
    tempP={ 0 , 175 , 45 , 50 };
    tempC={ tempP.x*2 , tempP.y*2 , tempP.w*2 , tempP.h*2 };
    QCTip.loadmedia( Bed.GiveTex( ) , &tempC ,&tempP , "n" );
    
    tempP={ 100 , 100 , 760 , 340 };
    tempC={ 0 , 0 , 0 , 0 };
    computer Computer( Bed.GiveTex( ) , &tempC , &tempP , "y" );
    
    
    Talking Hi("離開房間！,該上計程囉～");
    
    bool first=true;
    
    
    while( !quit ){
        SDL_SetRenderDrawColor( MainRenderer , 0 , 0 , 0 , 255 );
        SDL_RenderClear( MainRenderer );
        
        Background.render();
        
        RenderAll();
        
        Hi.render();
        
        mCollum.Show( );
        
        Computer.Show();
        
        SDL_RenderPresent( MainRenderer );
        
        if( !Hi.GetPop() && first ){
            Mix_VolumeMusic(40);
            music.play(-1);
            first=false;
        }
        
        if( Door.GetState()==State_Open ){
            SDL_Delay(500);
            quit=true;}
        
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT )
                quit=true;
            
            else if( e.type == SDL_MOUSEBUTTONDOWN ){
                
               
                if( (Bed.IsInside(&e) && Bed.GetState()==1) || (RDrawer.IsInside(&e)&& RDrawer.GetState()==1) ||  (LDrawer.IsInside(&e) && LDrawer.GetState()==1) || (QCTip.IsInside(&e) && QCTip.GetState()==0) )
                    found.play( 1 );
                
                click.play( 1 );
                
                
                Hi.ChangePop( e );
                
                Bed.ChangeState( e );
                
                if( mCollum.IsGet( 1 ) )
                    Door.ChangeState( e );
                
                if( !mCollum.IsGet( 1 ) && Door.IsInside( &e ) ){
                    err.play( 1 );
                    Hi.~Talking();
                    Hi.loadtext("似乎還沒有鑰匙喔");
                }
                
                LDrawer.ChangeState( e );
                
                if( mCollum.IsGet( 0 ) )
                    RDrawer.ChangeState( e );
                
                if( !mCollum.IsGet( 0 ) && RDrawer.IsInside( &e ) ){
                    err.play( 1 );
                    Hi.~Talking();
                    Hi.loadtext("似乎還沒有鑰匙喔");
                }
                
                QCTip.ChangeState( e );
                
                Computer.ChangeState( e );
                
                mCollum.CheckGet( &Bed , &LDrawer , &RDrawer , &QCTip );
                mCollum.ChangeSel( e );
                
            }
        }
    }
    Bed.~item();
    Door.~item( );
    LDrawer.~item( );
    RDrawer.~item();
    QCTip.~item();
    return RE;
}
//Class item
item::item( ){
    mHeight=0;
    mWidth=0;
    State=State_Oringin;
    TakeAway=false;
}
item::item( std::string path , SDL_Rect* Clip ,SDL_Rect* Paste , std:: string can ){
    loadmedia( path , Clip , Paste ,can );
    
}
item::item  ( mytexture* Tar , SDL_Rect* Clip , SDL_Rect* Paste ,std::string can ){
    loadmedia( Tar , Clip , Paste ,can );
    
}
item::~item(){
    free();
}
void item::free(){
    ItemTex.free();
}
int item::GetState(){
    return State;
}
void item::ChangeState( SDL_Event e ){
    if ( IsInside( &e ) ){
        if ( GetState( ) == State_Oringin && !TakeAway ){
            ClipPos={ ScreenPos.x*2 , ScreenPos.y*2 , ScreenPos.w*2 , ScreenPos.h*2 };
            State = State_Open;
        }
        else if( ( GetState( ) == State_Open && !TakeAway ) || ( GetState( ) == State_Oringin && TakeAway) ){
            if( !TakeAway ){
                ChangePic("Resource/RoomTakeaway.png");}
            TakeAway=true;
            State=State_TakeAway;
        }
        else if( CanClose )
            State = State_Oringin;
    }
}
void item::Render(){
    if( ClipPos.w == 0  )
        ItemTex.render( NULL , &ScreenPos );
    else
       ItemTex.render( &ClipPos , &ScreenPos );
}
void item::loadmedia( std::string path , SDL_Rect* Clip , SDL_Rect* Paste , std:: string can ){
    ItemTex.loadFromfile( path.c_str( ) );
    if ( Clip == NULL )
        ClipPos={ 0 , 0 , 0 , 0 };
    if( Paste == NULL )
        ScreenPos={ 0 , 0 , Width , Height };
    if( Clip != NULL )
        ClipPos = { Clip -> x , Clip -> y , Clip -> w , Clip -> h };
    if( Paste != NULL )
        ScreenPos = { Paste -> x , Paste -> y , Paste -> w , Paste -> h };
    mHeight = ScreenPos.h ;
    mWidth = ScreenPos.w ;
    State = State_Oringin;
    TakeAway=false;
    if( can[0] == 'n' )
        CanClose=false;
    else if( can[0] == 'y' )
        CanClose=true;
}
void item::loadmedia( mytexture* Tar , SDL_Rect* Clip , SDL_Rect* Paste , std:: string can ){
    ItemTex=*Tar;
    ClipPos = { Clip -> x , Clip -> y , Clip -> w , Clip -> h };
    ScreenPos = { Paste -> x , Paste -> y , Paste -> w , Paste -> h };
    mHeight = ScreenPos.h ;
    mWidth = ScreenPos.w ;
    State = State_Oringin;
    TakeAway=false;
    if( can[0] == 'n' )
        CanClose=false;
    else if( can[0] == 'y' )
        CanClose=true;
    
}
mytexture* item::GiveTex(){
    return &ItemTex;
}
void item::ChangeClip( const int x , const int y ){
    ClipPos.x = x;
    ClipPos.y = y;
}
void item::ChangePic( std::string Path ){
    ItemTex.loadFromfile( Path.c_str() );
}
bool item::IsInside( SDL_Event* e ){
    int x,y;
    SDL_GetMouseState( &x , &y );
    if( x < ScreenPos.x+ScreenPos.w && x > ScreenPos.x && y > ScreenPos.y && y < ScreenPos.y + ScreenPos.h ){
        return true;
    }
    else
        return false;
}
//Class ItemCollum
ItemCollum::ItemCollum ( ){
    Select = { 860 , 0 , 100 , 60 };
    for ( int i = 0 ; i < 6 ; i++ ){
        GetState[i]=false;
        Col[i]={ 860, i * 60 , 100 , 60 };
        Clip[i]={ 0, i * 120 , 200 , 120 };
    }
    FullTexture.loadFromfile("Resource/CollumFull.png");
    TipBackground.loadFromfile("Resource/tip_Collum.jpeg");
}
void ItemCollum::Show( ){
    SDL_SetRenderDrawColor( MainRenderer , 212 , 190 , 124 , 255 );
    for( int i = 0 ; i < 6 ; i++ ){
        SDL_RenderFillRect( MainRenderer , &Col[i] );
    }
    SDL_SetRenderDrawColor( MainRenderer , 0 , 0 , 0 , 255 );
    for( int i = 0 ; i < 6 ; i++ ){
        SDL_RenderDrawRect( MainRenderer , &Col[i] );
    }
    for( int i = 0 ; i < 6 ; i++ ){
        if( IsGet( i ) ){
            FullTexture.render( &Clip[i] , &Col[i] );
        }
    }
    SDL_SetRenderDrawColor( MainRenderer , 255 , 0 , 0 , 255 );
    SDL_RenderDrawRect( MainRenderer , &Select );
    
    if( pop==true && IsGet( PresentState ) ){
        bool quit=false;
        SDL_Event e;
        SDL_Rect Clip,TPaste={ 100 , 100 , 760 , 340 };
        mytexture temp;
        mymusic click("Resource/music/mouse clicks Sound Effect.wav","" );
        mymusic foundmu("Resource/music/CARTOON POP.wav","");
        mymusic Bfacemu("Resource/music/DUN DUN DUNNN.wav","");
        switch ( PresentState ) {
            case Num_DoorKey:
                temp.loadFromfile("Resource/key.png");
                Clip={ 0 , 0 , 2800 , 2800 };
                TPaste={ 280 , 70 , 400 , 400 };
                break;
            case Num_BoxKey:
                temp.loadFromfile("Resource/key.png");
                Clip={ 3600 , 0 , 2800 , 2800 };
                TPaste={ 280 , 70 , 400 , 400 };
                break;
            case Num_QCBox:
                temp.loadFromfile("Resource/QCBox.png");
                Clip={ 0 , 0 , 1000 , 800 };
                TPaste={ 230 , 70 , 500 , 400 };
                break;
            case Num_PicBox:
                temp.loadFromfile("Resource/PicBox.png");
                Clip={ 0 , 0 , 1640 , 1900 };
                TPaste={ 480-172 , 70 , 345 , 400 };
                break;
            case Num_BoxTip:
                temp.loadFromfile("Resource/Tip.png");
                Clip={ 0 , 0 , 2500 , 2500 };
                TPaste={ 280 , 70 , 400 , 400 };
                break;
            case Num_QCTip:
                temp.loadFromfile("Resource/Tip.png");
                Clip={ 3800 , 240 , 2300 , 2000 };
                TPaste={ 280 , 70 , 400 , 400 };
                break;
            default:
                break;
        }
        
        Uint32 pt=0,t=0;
        std::stringstream Ans;
        Ans.str("");
        int Press=0;
        bool input=true;
        bool Bfound=false;
        bool found=false;
        mytexture direction;
        mytexture Pic;
        mytexture BFace;
        SDL_Rect PicClip={ 0 , 0 , 792 , 1026 },PicPaste,DirPaste;
        Talking Talk("哎呀！被找到了！");
        SDL_Rect BClip;
        if( PresentState == Num_PicBox ){
            Pic.loadFromfile("Resource/Pic.png");
            direction.loadFromfile("Resource/Direct.png");
            DirPaste={ 700 , 200 , 200 , 240  };
            PicPaste={  345 , 240 , 330/2 , 413/2+10   };
            
        }
        enum{
            Pic_UP,
            Pic_DOWN,
            Pic_LEFT,
            Pic_RIGHT
        };
        while(!quit){
            SDL_Rect Paste={ 50 , 50 , 860 , 440 };
            SDL_SetRenderDrawColor( MainRenderer , 0 , 0 , 0 , 255 );
            SDL_RenderClear( MainRenderer );
            
            Background.render();
            
            RenderAll();
            
            
            
            TipBackground.render( NULL , &Paste );
            
            
            while(SDL_PollEvent( &e ) != 0 ){
                if( e.type == SDL_QUIT ){
                    quit=true;
                    pop=false;
                }
                else if( e.type == SDL_MOUSEBUTTONDOWN ){
                    click.play( 1 );
                    int x,y;
                    SDL_GetMouseState( &x , &y );
                    if( !( IsInsideRect( &Paste , x , y ) ) ){
                        quit = true ;
                        pop=false;
                    }
                    
                    if( PresentState == Num_QCBox ){
                        SDL_Rect QCClip[4];
                        SDL_Rect Rectan={ 625/2 , 180/2 , 340/2 , 330/2 },
                        Circle={ 1000/2 , 180/2 , 280/2 , 330/2 };
                        for( int i = 0 ; i < 4 ; i++ ){
                            QCClip[i]={ 1000*i , 0 , 1000 , 800 };
                        }
                        if(  IsInsideRect( &Rectan , x , y )  && t-pt>500 ){
                            Press = 2 ;
                            Clip = QCClip[Press];
                            pt=SDL_GetTicks();
                            input=true;
                        }
                        else if(  IsInsideRect( &Circle , x , y ) && t-pt>500 ){
                            Press=1;
                            Clip = QCClip[Press];
                            pt=SDL_GetTicks();
                            input=true;
                        }
                    }
                    else if( PresentState == Num_PicBox ){
                        int x,y;
                        SDL_GetMouseState( &x , &y );
                        
                        direction.render( NULL , &DirPaste );
                        SDL_Rect PicSClip[4];
                        SDL_Rect DirRect[4];
                        DirRect[Pic_DOWN]={770,215,55,80};
                        DirRect[Pic_UP]={770,350,55,80};
                        DirRect[Pic_RIGHT]={725,305,63,45};
                        DirRect[Pic_LEFT]={800,305,63,45};
                        
                        
                        for( int i = 0 ; i < 2 ; i++ ){
                            for( int j = 0 ; j<2 ;j++ ){
                                PicSClip[i*2+j]={ 792*i , 1026*j , 792 , 1026 };
                                
                                if( IsInsideRect( &DirRect[i*2+j] , x , y ) && t-pt > 500 ){
                                    Press=i*2+j;
                                    pt=SDL_GetTicks();
                                    input=true;
                                    srand((int)time(NULL));
                                    PicClip=PicSClip[rand()%4];
                                }
                            }
                        }
                    }
                    
                    if( found || Bfound ){
                        Talk.ChangePop( e );
                    }
                    
                    
                }
            }
            if( PresentState == Num_QCBox ){
                t=SDL_GetTicks();
            }
            if( t-pt>500 && PresentState == Num_QCBox ){
                Clip={ 0 , 0 , 1000 , 800 };
                if( Press == 1 && input ){
                    Ans<<"q";
                    input=false;
                }
                else if( Press ==2 && input ){
                    Ans<<"c";
                    input=false;
                }
                std::string TempAns=&Ans.str()[ std::strlen( &Ans.str()[0] ) - 5 ];
                if( TempAns == "qcqcc" ){
                    Clip={ 3000 , 0 , 1000 , 800 };
                    GetState[Num_BoxKey]=true;
                    if(!found){
                        foundmu.play( 1 );
                        Talk.loadtext("找到鑰匙了！");
                    }
                    found=true;
                }
            }
            else if( PresentState == Num_PicBox ){
                t=SDL_GetTicks();
                if( t-pt>500  && input ){
                    switch (Press) {
                        case 0:
                            Ans<<"u";
                            input=false;
                            break;
                        case 1:
                            Ans<<"d";
                            input=false;
                            break;
                        case 2:
                            Ans<<"l";
                            input=false;
                            break;
                        case 3:
                            Ans<<"r";
                            input=false;
                            break;
                        default:
                            break;
                    }
                }
                std::string TempAns=&Ans.str()[ std::strlen( &Ans.str()[0] ) - 3 ];
                std::string TempAns1=&Ans.str()[ std::strlen( &Ans.str()[0] ) - 10 ];
                if( TempAns == "ldr" ){
                    Clip={ 1640 , 0 , 1640 , 1900 };
                    GetState[Num_DoorKey]=true;
                    PicPaste={  345 , 230 , 330/2 , 413/2+20   };
                    if(!found){
                        Talk.loadtext("找到鑰匙了！");
                        foundmu.play( 1 );
                    }
                    found=true;
                    Bfound = false;
                }
                if( TempAns1 == "llllllllll" ){
                    BClip={164,84,460,620};
                    if( Talk.GetPop() && !Bfound ){
                        BFace.loadFromfile("Resource/Opening.bmp");
                        Bfacemu.play( 1 );
                        RE++;
                    }
                    Bfound=true;
                }
                
                Pic.render( &PicClip , &PicPaste );
            
                direction.render( NULL , &DirPaste );
                
            }
            temp.render( &Clip , &TPaste );
            if( Bfound && Talk.GetPop() ){
                BFace.render( &BClip , &PicPaste );
            }
            if( found || Bfound ){
                Talk.render();
            }
            SDL_RenderPresent(MainRenderer);
        }
    }
    
    
}
void ItemCollum::ChangeSel( SDL_Event e ){
    for( int i = 0 ; i < 6 ; i++ ){
        if ( IsInside( e , i ) && PresentState == i  ){
            Select = Col[i];
            PresentState = i ;
            pop=true;
        }
        if ( IsInside ( e , i ) && PresentState != i ){
            Select = Col[i];
            PresentState = i ;
            pop=false;
        }
    }
}
bool ItemCollum::IsInside( SDL_Event e , int i ){
    int x,y;
    SDL_GetMouseState( &x , &y );
    if( x < Col[i].x+Col[i].w && x > Col[i].x && y > Col[i].y && y < Col[i].y + Col[i].h ){
        return true;
    }
    else
        return false;
}
bool ItemCollum::IsGet( int required ){
    return GetState[required];
}
void ItemCollum::ChangeState( int i ){
    GetState[i]=true;
}
void ItemCollum::CheckGet( item* Bed , item* LDrawer , item* RDrawer , item* QCTip ){
    if( Bed->GetState() == State_TakeAway ){
        GetState[Num_BoxTip]=true;
    }
    if( LDrawer->GetState() == State_TakeAway ){
        GetState[Num_QCBox]=true;
    }
    if( RDrawer->GetState() == State_TakeAway ){
        GetState[Num_PicBox]=true;
    }
    if( QCTip->GetState() == State_Open ){
        GetState[Num_QCTip]=true;
    }
}
//Class Talking
Talking::Talking(){
    textR = NULL;
    text = NULL;
    backgroundR={0,0,0,0};
    background.loadFromfile("Resource/TalkingBack.png");
    pop=false;
    line=1;
}
Talking::Talking( std::string Tar ){
    std::string* texttext = NULL ;
    line=1;
    for(int i =0 ; i < strlen( &Tar[0] ) ; i++ ){
        if(Tar[i]== ',' )
            line+=1;
    }
    texttext = new std::string[ line ];
    char* tokenPtr;
    tokenPtr = strtok( &Tar[0] , ",");
    for ( int i=0 ;tokenPtr != NULL ; i++ )
    {
        texttext[i]=tokenPtr;
        tokenPtr = strtok(NULL, " ");
    }
    
    text = new mytexture[ line ];
    for(int i=0 ; i < line ; i++ ){
        text[i].loadText( texttext[i] , 0 , 0 , 0 , 50 );
    }
    
    for( int i=0 ; i < line ; i++ ){
        if( text[i].getwidth() > MaxWidth )
        MaxWidth=text[i].getwidth();
    }
    
    textR=new SDL_Rect [line];
    
    for( int i = 0 ; i < line ; i++ ){
        textR[i].w=text[i].getwidth();
        textR[i].h=text[i].getheight();
    }
    
    backgroundR.w=MaxWidth+50;
    backgroundR.h=textR[0].h*line+50;
    background.loadFromfile("Resource/TalkingBack.png");
    pop=true;
    delete [] texttext ;
}
Talking::~Talking(){
    free();
}
bool Talking::GetPop(){
    return pop;
}
void Talking::render(){
    if(pop){
        for(int i = 0 ; i < line ; i++ ){
            textR[i].x=480-textR[i].w/2;
            textR[i].y=270-(textR[i].h*line)/2+textR[i].h*i;
        }
        backgroundR.x=480-backgroundR.w/2;
        backgroundR.y=270-backgroundR.h/2;
        background.render( NULL , &backgroundR );
        for(int i=0 ; i< line ; i++ ){
            text[i].render( NULL , &textR[i] );
        }
    }
}
void Talking::ChangePop( SDL_Event e ){
    int x,y;
    SDL_GetMouseState( &x , &y );
    if( !IsInsideRect( &backgroundR , x , y ) ){
        pop=false;
        free();
    }
}
void Talking::loadtext( std::string Tar ){
    std::string* texttext = NULL ;
    line=1;
    for(int i =0 ; i < strlen( &Tar[0] ) ; i++ ){
        if(Tar[i]== ',' )
        line+=1;
    }
    texttext = new std::string[ line ];
    char* tokenPtr;
    tokenPtr = strtok( &Tar[0] , ",");
    for ( int i=0 ;tokenPtr != NULL ; i++ )
    {
        texttext[i]=tokenPtr;
        tokenPtr = strtok(NULL, " ");
    }
    
    text = new mytexture[ line ];
    for(int i=0 ; i < line ; i++ ){
        text[i].loadText( texttext[i] , 0 , 0 , 0 , 50 );
    }
    
    for( int i=0 ; i < line ; i++ ){
        if( text[i].getwidth() > MaxWidth )
        MaxWidth=text[i].getwidth();
    }
    
    textR=new SDL_Rect [line];
    
    for( int i = 0 ; i < line ; i++ ){
        textR[i].w=text[i].getwidth();
        textR[i].h=text[i].getheight();
    }
    
    backgroundR.w=MaxWidth+50;
    backgroundR.h=textR[0].h*line+50;
    background.loadFromfile("Resource/TalkingBack.png");
    pop=true;
    delete [] texttext ;
}
void Talking::free(){
    pop=false;
    for(int i=0 ;i < line ; i++ ){
        if(&text[i]!=NULL)
            text[i].free();
    }
    textR=NULL;
    background.free();
}
//Class computer
void computer::ChangeState( SDL_Event e ){
    int x,y;
    SDL_GetMouseState( &x , &y );
    if( !pop ){
        if( IsInsideRect( &ScreenPos , x , y ) ){
            pop=true;
            background.loadFromfile("Resource/tip_collum.jpeg");
        }
    }
}
void computer::Show(){
    
    if(pop){
        item::ChangePic("Resource/Desktop.png");
        mymusic click("Resource/music/mouse clicks Sound Effect.wav","" );
        mymusic saywhat("Resource/music/SAY WHAT.wav","");
        enum{
            CState_Or,
            CState_Qu,
            CState_Co,
            CState_Tr
        };
        bool quit=false;
        bool qc=false , co = false ;
        SDL_Event e;
        Talking Talk;
        int x,y;
        int state=CState_Or;
        bool first=true;
        SDL_Rect QuRect={ 400/2 , 390/2 , 170/2 , 100/2 },
                CoRect={ 440/2 , 500/2 , 170/2 , 100/2 },
                TrRect={ 420/2 , 250/2 , 170/2 , 100/2 },
                quitRect={1330/2,280/2,15,15};
        while( !quit ){
            
            if( state == CState_Qu && !Talk.GetPop() && first ){
                
                    item::free();
                    Talk.free();
                    item::ChangePic( "Resource/Desktop_quartus.png" );
                    Talk.loadtext("沒時間搞 quartus ii 了！,快去上課！");
                    qc=true;
                
            }
            
            if( state == CState_Co && !Talk.GetPop() && first ){
                
                item::free();
                Talk.free();
                item::ChangePic( "Resource/Desktop_Code.png" );
                Talk.loadtext("我的 Code Bug 超多,去上課還比較實在！");
                co=true;
                
            }
            
            if( state == CState_Tr && !Talk.GetPop() && first && co && qc ){
                RE++;
                item::free();
                Talk.free();
                item::ChangePic( "Resource/Desktop_open.png" );
                Talk.loadtext("柏廷的資料夾？,也太噁了吧...");
                saywhat.play( 1 );
                
            }
            
            if( state == CState_Or && !first ){
                item::free();
                Talk.free();
                item::ChangePic("Resource/Desktop.png");
                first=true;
                
            }
            
            
            
            SDL_SetRenderDrawColor(MainRenderer, 0 , 0 , 0 , 255 );
            SDL_RenderClear(MainRenderer);
            Background.render();
            RenderAll();
            background.render( NULL , &RBackground );
            item::Render();
            Talk.render();
            SDL_RenderPresent( MainRenderer );
            
            
            while( SDL_PollEvent( &e ) != 0 ){
                if(e.type==SDL_MOUSEBUTTONDOWN){
                    click.play( 1 );
                    SDL_GetMouseState( &x , &y );
                    if( !IsInsideRect( &RBackground , x , y )){
                        quit=true;
                        pop=false;
                        background.free();
                    }
                    else if( IsInsideRect( &QuRect , x , y ) ){
                        state = CState_Qu;
                    }
                    else if( IsInsideRect( &CoRect , x , y ) ){
                        state=CState_Co;
                    }
                    else if( IsInsideRect( &TrRect , x , y ) ){
                        state=CState_Tr;
                        
                    }
                    if(  state != CState_Or  && Talk.GetPop() ){
                        Talk.ChangePop( e );
                        if( !Talk.GetPop() )
                            first=false;
                    }
                    
                    else if (  state != CState_Or  && !Talk.GetPop() ){
                        if( IsInsideRect( &quitRect , x , y ) )
                            state=CState_Or;
                    }
                    
                    
                    
                }
            }
            
        
        
        }
        item::free();
    }
    
}

//Functions
bool IsInsideRect( SDL_Rect* Tar , const int x , const int y ){
    if(  x < Tar->x+Tar->w && x > Tar->x && y > Tar->y && y < Tar->y + Tar->h  ){
        return true;
    }
    else return false;
}
void RenderItem( item* Tar ){
    if( Tar->GetState( ) != State_Oringin ){
        Tar->Render( );\
    }
}
void RenderAll( ){
    RenderItem( &Door );
    RenderItem( &Bed );
    RenderItem( &LDrawer );
    RenderItem( &RDrawer );
    RenderItem( &QCTip );
}
