#ifndef myTexture_hpp
#define myTexture_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include "backgroundfunction.hpp"

using namespace std;

extern SDL_Renderer* MainRenderer;
extern TTF_Font* gFont;
extern Uint8 fade;

class myTexture
{
public:
    
    myTexture();
    ~myTexture();
    
    bool loadFromFile(string path);
    
#ifdef _SDL_TTF_H
    bool loadFromRenderedText(string textureText,SDL_Color textColor);
#endif
   
    void fadeout();
    void free();
    void setColor_BlendMode_Alpha( Uint8 red, Uint8 green, Uint8 blue ,SDL_BlendMode blending,Uint8 alpha );
    void render( int x, int y, SDL_Rect* clip = NULL);
    
    int getWidth();
    int getHeight();
    
private:
    
    SDL_Texture* mTexture;
    
    int mWidth;
    int mHeight;
};

#endif /* myTexture_hpp */
