#ifndef TEXTURE

#define TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/log.hpp"

struct Texture{
    SDL_Renderer* renderer;
    SDL_Rect* textureRectangle;
    SDL_Texture* textureTexture;
    SDL_Surface* textureSurface;

    bool initTexture(SDL_Renderer* renderer, const char* src);

    bool loadTexture(const char* src);

    
};




#endif