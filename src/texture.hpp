#ifndef TEXTURE

#define TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "log.hpp"

struct Texture{
    SDL_Renderer* renderer;
    const char* src{""};
    SDL_Surface *surface;
    SDL_Texture* texture;
    SDL_Rect* rectangle;

    void loadImage();
    void loadImage(const char* src);
    
    Texture();
    Texture(SDL_Renderer*);
    Texture(SDL_Renderer* renderer, int16_t x, int16_t y, uint16_t w, uint16_t h,const char* src);

    ~Texture();
};



#endif