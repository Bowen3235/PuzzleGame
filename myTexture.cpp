#include "myTexture.hpp"

myTexture::myTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

myTexture::~myTexture()
{
    free();
}

bool myTexture::loadFromFile(string path )
{
    free();
    
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB( loadedSurface->format,0,0xFF,0xFF));
    
    newTexture = SDL_CreateTextureFromSurface( MainRenderer, loadedSurface );
    
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    
    SDL_FreeSurface( loadedSurface );
    
    mTexture = newTexture;
    
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool myTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    free();
    
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    
    mTexture = SDL_CreateTextureFromSurface( MainRenderer, textSurface );
    
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    
    SDL_FreeSurface( textSurface );
    
    return mTexture != NULL;
}
#endif

void myTexture::fadeout()
{
    if(fade-4<0)fade = 0;
    else fade-=4;
    
    setColor_BlendMode_Alpha(255, 0, 0, SDL_BLENDMODE_BLEND, fade);
}

void myTexture::free()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

void myTexture::setColor_BlendMode_Alpha( Uint8 red,Uint8 green,Uint8 blue,SDL_BlendMode blending,Uint8 alpha )
{
    SDL_SetTextureColorMod( mTexture, red, green, blue );
    SDL_SetTextureBlendMode( mTexture, blending );
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void myTexture::render(int x,int y,SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    SDL_RenderCopy( MainRenderer, mTexture, clip, &renderQuad);
}

int myTexture::getWidth()
{
    return mWidth;
}

int myTexture::getHeight()
{
    return mHeight;
}
