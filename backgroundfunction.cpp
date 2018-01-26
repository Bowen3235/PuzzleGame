//
//  backgroundfunction.cpp
//  final project_demo
//
//  Created by nettoycrick on 11/12/2017.
//  Copyright © 2017 nettoycrick. All rights reserved.
//

#include "backgroundfunction.hpp"

SDL_Window* MainWindow=NULL;
SDL_Renderer* MainRenderer=NULL;

mytexture::mytexture(){
    
}

mytexture::mytexture(std::string path){
    loadFromfile(path);
}

mytexture::~mytexture(){
    if(TheTexture!=NULL){
        free();
        Destroy=true;
    }
}

void mytexture::free(){
    if(TheTexture!=NULL&&!Destroy){
        SDL_DestroyTexture(TheTexture);
        Destroy=true;
        TheTexture=NULL;}
}

void mytexture::freefrombackground(){
    SDL_SetRenderTarget( MainRenderer, NULL );
};

void mytexture::settobackground(){
    background=true;
    TheTexture=SDL_CreateTexture(MainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);
    SDL_SetRenderTarget( MainRenderer, TheTexture );
};

void mytexture :: render(SDL_Rect* clip,SDL_Rect* Paste){
    SDL_RenderCopy(MainRenderer,
                     TheTexture,
                     clip, Paste);
};

void mytexture :: render(SDL_Rect* clip,
                SDL_Rect* Paste,
                double Degree,
                const SDL_Point* center,
                const SDL_RendererFlip flip){
        SDL_RenderCopyEx(MainRenderer,
                         TheTexture,
                         clip, Paste,
                         Degree,
                         center,
                         flip);
    };
void mytexture :: loadFromfile(std::string path ){
    free();
    Destroy=false;
    SDL_Surface* LoadedSurface;
    LoadedSurface=IMG_Load(path.c_str());
    SDL_SetColorKey(LoadedSurface, SDL_TRUE,SDL_MapRGB( LoadedSurface->format, 0, 0, 1 ));
    TheTexture=SDL_CreateTextureFromSurface(MainRenderer, LoadedSurface);
    mHeight=LoadedSurface->h;
    mWidth=LoadedSurface->w;
    if(TheTexture==NULL)
         printf("Failed to Load Texture");
    SDL_FreeSurface(LoadedSurface);
    SDL_SetTextureAlphaMod( TheTexture , 255 );
    load=true;
    };
void mytexture :: loadText(std::string text,Uint8 r,Uint8 g,Uint8 b , const int size ){
    SDL_Color color={r,g,b};
    TTF_Init();
    TTF_Font* Font;
    Font=TTF_OpenFont("ReSource/Kaiti.ttc", size);
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( Font, text.c_str(), color );
    TheTexture = SDL_CreateTextureFromSurface( MainRenderer, textSurface );
    mHeight=textSurface->h;
    mWidth=textSurface->w;
    SDL_FreeSurface( textSurface );
    TTF_CloseFont( Font );
    Font=NULL;
    TTF_Quit();
    load=true;
    Destroy=false;
};
int mytexture::getwidth(){
    return mWidth;
}
int mytexture::getheight(){
    return mHeight;
}
void init(){
    SDL_Rect Fill={0,0,Height,Width};
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    MainWindow=SDL_CreateWindow("The Final Project", 200 , 200, Width, Height,  SDL_WINDOW_SHOWN);
    MainRenderer=SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor( MainRenderer, 0, 0, 0, 0xFF );
    SDL_RenderClear(MainRenderer);
    IMG_Init( IMG_INIT_PNG );
    Mix_Init( MIX_INIT_MP3 );
    SDL_SetRenderDrawColor(MainRenderer,0,0,0,225);
    SDL_RenderFillRect(MainRenderer,&Fill);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}
void close()
{
    SDL_DestroyRenderer( MainRenderer );
    SDL_DestroyWindow( MainWindow );
    MainWindow = NULL;
    MainRenderer = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
void fadein(const int t,mytexture* Target){
    SDL_SetTextureBlendMode( Target->TheTexture,SDL_BLENDMODE_BLEND );
    Uint32 time=SDL_GetTicks();
    Uint32 nowtime;
    Uint32 inTime=SDL_GetTicks();
    Uint32 TTime;
    for(int i=0;i<50;i++){
        time=SDL_GetTicks();
        SDL_SetRenderDrawColor(MainRenderer,0,0,0,225);
        SDL_RenderFillRect(MainRenderer,NULL);
        SDL_SetTextureAlphaMod( Target->TheTexture , i*5);
        Target->render(NULL,NULL);
        SDL_RenderPresent(MainRenderer);
        nowtime=SDL_GetTicks();
        nowtime-=time;
        TTime=SDL_GetTicks();
        if(nowtime<t*1000/50&& t*1000>TTime-inTime)
            SDL_Delay(t*1000/50-nowtime);
    }
}
void fadeout(const int t,mytexture* Target){
    SDL_SetTextureBlendMode( Target->TheTexture,SDL_BLENDMODE_BLEND );
    Uint32 time=SDL_GetTicks();
    Uint32 nowtime;
    Uint32 inTime=SDL_GetTicks();
    Uint32 TTime;
    for(int i=0;i<50;i++){
        time=SDL_GetTicks();
        SDL_RenderClear(MainRenderer);
        SDL_SetRenderDrawColor(MainRenderer,0,0,0,255);
        SDL_RenderFillRect(MainRenderer,NULL);
        SDL_SetTextureAlphaMod( Target->TheTexture , 255 - i*5 );
        Target->render(NULL,NULL);
        SDL_RenderPresent(MainRenderer);
        nowtime=SDL_GetTicks();
        nowtime-=time;
        TTime=SDL_GetTicks();
        if(nowtime<t*1000/50 && t*1000>TTime-inTime)
            SDL_Delay(t*1000/50-nowtime);
    }
}
//mymissic
mymusic::mymusic(){
    playbool=false;
    music=false;
}
void mymusic::loadmusic( std::string path , std::string mu){
    playbool=false;
    if( mu == "music" ){
        music=true;
        Themusic=Mix_LoadMUS( path.c_str() );
        Thechunk=NULL;
    }
    else{
        music=false;
        Thechunk=Mix_LoadWAV( path.c_str() );
        Themusic=NULL;
    }
}
mymusic::mymusic( std::string path , std::string mu ){
    loadmusic( path , mu );
}
void mymusic::play( int num ){
    if( music && !playbool ){
        Mix_PlayMusic( Themusic , num );
        playbool=true;
    }
    else if( !music ){
        Mix_VolumeChunk(Thechunk, 90);
        Mix_PlayChannel( -1 , Thechunk , num- 1 );
    }
}
void mymusic::pause(){
    if( playbool )
        Mix_PausedMusic();
}
void mymusic::changestate( bool next ){
    playbool=next;
}
void mymusic::free(){
    if( music ){
        Mix_FreeMusic( Themusic );
    }
    else{
        Mix_FreeChunk( Thechunk );
    }
}
mymusic::~mymusic(){
    free();
}


