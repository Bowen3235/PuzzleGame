#ifndef exWindow_hpp
#define exWindow_hpp

#include "myTexture.hpp"

extern const int exScreen_Width;
extern const int exScreen_Height;

extern SDL_Window* exWindow;
extern SDL_Renderer* exRenderer;
extern SDL_Texture* exTexture;
extern bool quit;

bool exinit(int i);
bool exloadMedia(int i);
void exclose();
void exWindow1(int i);

#endif /* exWindow_hpp */
