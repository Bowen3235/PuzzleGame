 #include "exWindow.hpp"

using namespace std;

const int exScreen_Width = 640;
const int exScreen_Height = 480;

SDL_Window* exWindow = NULL;
SDL_Renderer* exRenderer = NULL;
SDL_Texture* exTexture;

bool exinit(int i)
{
    bool success = true;
    
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    
    switch (i)
    {
        case 1:
            exWindow = SDL_CreateWindow( "總圖書館", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 2:
            exWindow = SDL_CreateWindow( "普通教學館", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 3:
            exWindow = SDL_CreateWindow( "德田館", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 4:
            exWindow = SDL_CreateWindow( "舊體育館", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 5:
            exWindow = SDL_CreateWindow( "保健中心", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 6:
            exWindow = SDL_CreateWindow( "足球場", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 7:
            exWindow = SDL_CreateWindow( "活大", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 8:
            exWindow = SDL_CreateWindow( "小福樓", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
        case 9:
            exWindow = SDL_CreateWindow( "博理館", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, exScreen_Width, exScreen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            break;
    }
    mymusic din("Resource/music/DING.wav","");
    din.play( 1 );
    
    exRenderer = SDL_CreateRenderer( exWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    
    SDL_SetRenderDrawColor( exRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }
    return success;
}

bool exloadMedia(int i)
{
    bool success = true;
    SDL_Surface* loadedSurface = NULL;
    switch(i)
    {
        case 1:
            loadedSurface = IMG_Load("Resource/總圖.png");
            break;
        case 2:
            loadedSurface = IMG_Load("Resource/普通.png");
            break;
        case 3:
            loadedSurface = IMG_Load("Resource/德田.png");
            break;
        case 4:
            loadedSurface = IMG_Load("Resource/舊體.png");
            break;
        case 5:
            loadedSurface = IMG_Load("Resource/保健中心.png");
            break;
        case 6:
            loadedSurface = IMG_Load("Resource/足球場.png");
            break;
        case 7:
            loadedSurface = IMG_Load("Resource/活大.png");
            break;
        case 8:
            loadedSurface = IMG_Load("Resource/小福.png");
            break;
        case 9:
            loadedSurface = IMG_Load("Resource/博理.png");
            break;
    }
    
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB( loadedSurface->format,0,0xFF,0xFF));
    
    exTexture = SDL_CreateTextureFromSurface( exRenderer, loadedSurface );
    
    SDL_FreeSurface( loadedSurface );
    
    return success;
}

void exclose()
{
    SDL_DestroyTexture(exTexture);
    SDL_DestroyRenderer( exRenderer );
    SDL_DestroyWindow( exWindow );
    exWindow = NULL;
    exRenderer = NULL;
}

void exWindow1(int i)
{
    mymusic pop("Resource/music/CARTOON POP.wav", "");
    if(i<10)
    {
        exinit(i);
        exloadMedia(i);
        SDL_Event ex;
        
        pop.play( 1 );
        bool exquit = false;
    
        while( !exquit )
        {
            while( SDL_PollEvent( &ex ) != 0 )
            {
                if(ex.type == SDL_KEYDOWN)if(ex.key.keysym.sym == SDLK_SPACE)exquit = true;
            }
        
            SDL_SetRenderDrawColor( exRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( exRenderer );
            SDL_RenderCopy(exRenderer, exTexture, NULL, NULL);
        
            SDL_RenderPresent( exRenderer );
        }
    
        exclose();
    }
    else quit = true;
}

