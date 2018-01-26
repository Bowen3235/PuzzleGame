//
//  backgroundfunction.hpp
//  final project_demo
//
//  Created by nettoycrick on 11/12/2017.
//  Copyright © 2017 nettoycrick. All rights reserved.
//

#ifndef backgroundfunction_hpp
#define backgroundfunction_hpp

#include <stdio.h>

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2_mixer/SDL_mixer.h>
#include<string>
#include<sstream>

#define Height 540
#define Width 960
extern SDL_Window* MainWindow;
extern SDL_Renderer* MainRenderer;



class mytexture{
    friend void fadeout(const int,mytexture*);
    friend void fadein(const int,mytexture*);
private:
    bool Destroy=true;
    int x=0;
    int y=0;
    bool background=false;
    int mWidth=0;
    int mHeight=0;
    SDL_Texture* TheTexture;
    bool load=false;
public:
    mytexture();
    mytexture(std::string);
    ~mytexture();
    SDL_Rect Whole={0,0,mHeight,mWidth};
    bool IsLoad(){
        return load;
    };
    void render(SDL_Rect* clip=NULL,SDL_Rect* Paste=NULL);
    void render(SDL_Rect* clip,
                 SDL_Rect* Paste,
                 double Degree,
                 const SDL_Point* center,
                 const SDL_RendererFlip flip);
    void loadFromfile(std::string path );
    void loadText(std::string , Uint8 , Uint8 , Uint8 , const int );
    void settobackground();
    void freefrombackground();
    void free();
    int getwidth();
    int getheight();
};
class mymusic{
public:
    mymusic();
    mymusic( std:: string , std::string  );
    ~mymusic();
    void free();
    void play( int );
    void pause();
    void changestate( bool );
    void loadmusic( std::string , std::string );
    bool getstate(){
        return playbool;
    };
private:
    Mix_Chunk *Thechunk=NULL;
    Mix_Music *Themusic=NULL;
    bool playbool;
    bool music;
    
};


void init();//Done
void close();//Done
void fadein (const int t,mytexture *Target);
void fadeout(const int t,mytexture *Target);


#endif /* backgroundfunction_hpp */
