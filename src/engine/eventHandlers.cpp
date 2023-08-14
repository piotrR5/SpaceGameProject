#include "Engine.hpp"

void Engine::eventHandler(bool& run){
    SDL_Event event;
    camera.move();

    while (SDL_PollEvent(&event)) {

        bool ok;

        switch (event.type) {
        case SDL_QUIT:
            run = false;
            log("quitting");
        break;

        case SDL_KEYDOWN:
            onKeyPress(event, run);
        break;
        case SDL_KEYUP:
            onKeyRelease(event, run);
        break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseClick(event, run);
        break;
        case SDL_MOUSEBUTTONUP:
            onMouseRelease(event, run);
        break;
        case SDL_MOUSEWHEEL:
            onMouseScroll(event, run);
        break;
        }
    }
}

void Engine::onKeyPress(SDL_Event event, bool& run){
    //log("Key pressed");
    if(event.key.keysym.sym==SDLK_q){
        run=false;
        return;
    }
    if(event.key.keysym.sym==SDLK_m){
        gui.visible=!gui.visible;
    }
    if(event.key.keysym.sym==SDLK_w){
        camera.velocity.y=-10;
    }   
    if(event.key.keysym.sym==SDLK_s){
        camera.velocity.y=10;
    }
    if(event.key.keysym.sym==SDLK_d){
        camera.velocity.x=10;
    }
    if(event.key.keysym.sym==SDLK_a){
        camera.velocity.x=-10;
    }
}

void Engine::onKeyRelease(SDL_Event event, bool& run){
    //log("Key released");
    if(event.key.keysym.sym==SDLK_w){
        camera.velocity.y=0;
    }   
    if(event.key.keysym.sym==SDLK_s){
        camera.velocity.y=0;
    }
    if(event.key.keysym.sym==SDLK_d){
        camera.velocity.x=0;
    }
    if(event.key.keysym.sym==SDLK_a){
        camera.velocity.x=0;
    }
}

void Engine::onMouseClick(SDL_Event event, bool& run){
    int mouse_x,mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        log("Left mouse button clicked.");
        logOK("Mouse coords : "); cout << mouse_x << " "<<mouse_y<<endl;
        vec2 mouseInGamePos = camera.ConvertToWorldCoords({mouse_x,mouse_y});
        cout<<"Conversion : " << mouseInGamePos.x<<" " << mouseInGamePos.y<<endl;
        OH.isObjectClicked(mouseInGamePos.x, mouseInGamePos.y);
    }
    else if(event.button.button == SDL_BUTTON_RIGHT)
    {
        log("Right mouse button clicked.");
        vec2 mouseInGamePos = camera.ConvertToWorldCoords({mouse_x,mouse_y});
        OH.addToMovementList(mouseInGamePos.x, mouseInGamePos.y);
    }
    else if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        log("Scroll pressed.");
    }
}

void Engine::onMouseRelease(SDL_Event event, bool& run){
    log("Mouse button released");
}

void Engine::onMouseScroll(SDL_Event event, bool& run){
    log("Mouse scrolled");
    if(event.wheel.y > 0){
        camera.rescale(1.05);
    }else if(event.wheel.y < 0 ){
        camera.rescale(0.95);
    }
}