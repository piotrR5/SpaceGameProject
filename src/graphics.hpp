#ifndef GRAPHICS

#define GRAPHICS

#include "camera.hpp"
#include "constants.hpp"

#include "entity-background.hpp"

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>


class Engine{
    uint16_t fps=60;
    uint16_t desiredDT=1000/fps;

public:
    std::vector<Entity>entities;
    Camera camera;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect* windowRect;
    EntityBackground back{nullptr, "assets/missingTexture.png"};
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

    void loadSkybox();
    void drawSkybox();

    Engine();

    ~Engine();
}; 


#endif
