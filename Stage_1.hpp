//
//  Stage_1.hpp
//  final project_demo
//
//  Created by nettoycrick on 2017/12/28.
//  Copyright © 2017年 nettoycrick. All rights reserved.
//

#ifndef Stage_1_hpp
#define Stage_1_hpp

#include <stdio.h>
#include "backgroundfunction.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
enum
{
    State_Oringin,
    State_Open,
    State_TakeAway,
};

int stage_1( );

class item{
private:
    mytexture ItemTex;
    SDL_Rect  ScreenPos;
    SDL_Rect  ClipPos;
    int       mHeight,mWidth;
    int       State;
    bool      TakeAway;
    bool      CanClose=true;
public:
    item ( );   //Done
    item ( std::string , SDL_Rect* , SDL_Rect* , std::string );   //Done
    item ( mytexture* , SDL_Rect* , SDL_Rect*  , std::string );    //Done
    ~item( );   //Done
    void loadmedia( std::string , SDL_Rect* , SDL_Rect* , std::string  );  //Done
    void loadmedia( mytexture* , SDL_Rect* , SDL_Rect* , std::string  ); //Done
    mytexture* GiveTex();   //Done
    int GetState( );    //Done
    void ChangeState( SDL_Event );   //Done
    void Render( );
    void ChangeClip( const int , const int );
    void ChangePic( std::string );
    bool IsInside( SDL_Event*  );
    void free();
};

class ItemCollum{
private:
    enum{
        Num_BoxKey,
        Num_DoorKey,
        Num_QCBox,
        Num_PicBox,
        Num_BoxTip,
        Num_QCTip,
        Num_Total
    };
    bool GetState[Num_Total];
    mytexture FullTexture;
    int PresentState;
    SDL_Rect Collum , Select ;
    SDL_Rect Clip[6];
    SDL_Rect Col[6];
    bool pop=false;
    mytexture TipBackground;
public:
    ItemCollum ( ); //Done
    bool IsGet ( int ); //Done
    void ChangeSel( SDL_Event ); //Done
    bool IsInside ( SDL_Event , int ); //Done
    void Show     ( ); //Done
    void ChangeState( int );
    void CheckGet( item* , item* ,item* ,item* );
};

class Talking{
private:
    bool pop=false;
    mytexture* text;
    mytexture background;
    SDL_Rect backgroundR;
    SDL_Rect* textR;
    int line;
    int MaxWidth=0;
public:
    Talking( );
    Talking( std::string );
    ~Talking();
    void loadtext( std::string );
    void render( );
    bool GetPop( );
    void ChangePop( SDL_Event );
    void free();
};

class Achieve{
private:
    int  num;
    bool BFace;
    bool HFloder;
public:
    Achieve();
    ~Achieve();
    int  getnum    (      );
    void SetBFace  ( bool );
    void SetHFloder( bool );
    bool IsBface   (      );
    bool IsHFloder (      );
};

class computer : public item{
private:
    SDL_Rect ScreenPos = { 362 , 300 , 175 , 125 };
    SDL_Rect RBackground = { 50 , 50 , 860 , 440 };
    mytexture background;
    mytexture *Desktop;
    bool pop=false;
public:
    computer( std::string path , SDL_Rect* Clip , SDL_Rect* Paste , std::string can ){
        item::loadmedia( path , Clip , Paste , can );
        Desktop=item::GiveTex();
    }
    computer( mytexture* Tar , SDL_Rect* Clip , SDL_Rect* Paste ,std::string can ){
        item::loadmedia( Tar , Clip , Paste ,can );
    };
    void ChangeState( SDL_Event );
    void Show( );
    
    
};

void RenderAll( );

void RenderItem( item* );

bool IsInsideRect( SDL_Rect* , const int ,const int );


#endif /* Stage_1_hpp */
