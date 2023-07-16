#ifndef GLOBALS

#define GLOBALS

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "utils/log.hpp"

#include "globals.hpp"

#define global Globals::instance() 

class Globals
{
public:
    static Globals& instance()
    {
        static Globals instance_;
        return instance_;
    }
    SDL_Renderer* renderer;
    TTF_Font* font;
private:
    Globals() {};
    Globals(const Globals&) {};
    ~Globals() {}
};




#endif



