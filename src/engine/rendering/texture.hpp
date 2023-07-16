#ifndef TEXTURE

#define TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/log.hpp"
#include "../globals.hpp"


struct Texture{
    SDL_Rect* textureRectangle;
    SDL_Texture* textureTexture;

    bool initTexture(const char* src);
    bool initTexture(SDL_Texture* txt, SDL_Rect* rect);

    bool loadTexture(const char* src);
};




#endif