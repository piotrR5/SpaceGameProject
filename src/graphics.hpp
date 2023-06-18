#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#ifndef GRAPHICS

#define GRAPHICS

#include "camera.hpp"
#include "constants.hpp"

#include "entities.hpp"

struct Background{
    SDL_Renderer* renderer;
    const char* src{""};
    SDL_Surface *background;
    SDL_Texture* backgroundTexture;
    SDL_Rect* backgroundRect;
    void loadImage();
};


class Engine{
    uint16_t fps=60;
    uint16_t desiredDT=1000/fps;

public:
    std::vector<Entity>entities;
    Camera camera;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect* windowRect;
    Background back1;
    int mouse_x, mouse_y;
    
    int getFps() {return fps;}
    /**
     * @return
     * @brief sets given fps
     * @param f
    */
    void setFps(uint8_t _fps) {fps=_fps; desiredDT=1000/_fps;}

    /**
     * @brief function handles events and changes [run] to false if program is to be exited
    */
    void eventHandler(bool& run);

    void mainMenuEventHandler(bool& run, bool& start);

    /**
     * @brief function stores the main program loop, primary and periodic logic is done inside
    */
    bool mainLoop();

    bool mainMenuLoop();

    void drawEntities();

    void updateEntities();

    Engine();

    ~Engine();
}; 


#endif
