#ifndef ENGINE

#define ENGINE

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils/sg_math.hpp"
#include "utils/log.hpp"

using std::cout;
using std::endl;

struct Engine{
private:
    bool wasInitialised;


    uint16_t fps, desiredDT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect* windowRectangle;
    

    void eventHandler(bool& run);

    void fpsHandler(int start);


public:
    int getFps();
    void setFps(uint16_t fps);

    bool engineInit();
    
    void mainLoop();


    Engine();
    ~Engine();
};

#endif