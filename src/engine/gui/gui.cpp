#include "gui.hpp"

bool Gui::initGui(const char* src, SDL_Rect* windowRect, int x, int y){
    if(global.renderer == nullptr){
        logErr("renderer is nullptr");
        exit(0);
    }
    guiBackground.initTexture(src);
    this->x=x;
    this->y=y;
    visible=false;

    this->windowRect=windowRect;

    windowRect->h=MENU_HEIGHT;
    windowRect->w=MENU_WIDTH;
    windowRect->x=50;
    windowRect->y=50;
}

void Gui::addButton(Button btn){
    buttons.push_back(btn);
}

bool Gui::inlineTextureRenderer(){
    auto& t=guiBackground;
    SDL_Rect* foo=new SDL_Rect;
    foo->x=t.textureRectangle->x;
    foo->y=t.textureRectangle->y;
    foo->w=t.textureRectangle->w;
    foo->h=t.textureRectangle->h;

    SDL_RenderCopy(global.renderer, t.textureTexture, foo, windowRect);

    for(auto b : buttons){
        b.renderButton();
    }

    return true;
}

bool Gui::renderGui(){
    if(!visible)return true;

    inlineTextureRenderer();

    return true;
}

void Gui::eventHandler(bool& run){
    SDL_Event event;
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

void Gui::onKeyPress(SDL_Event event, bool& run){
    log("Key pressed");
    if(event.key.keysym.sym==SDLK_q){
        run=false;
        return;
    }
    if(event.key.keysym.sym==SDLK_m){
        visible=!visible;
    }
    if(event.key.keysym.sym==SDLK_w){
    }   
    if(event.key.keysym.sym==SDLK_s){
    }
    if(event.key.keysym.sym==SDLK_d){
    }
    if(event.key.keysym.sym==SDLK_a){
    }
    if(event.key.keysym.sym==SDLK_ESCAPE){
        visible=false;
    }
}

void Gui::onKeyRelease(SDL_Event event, bool& run){
    log("Key released");
    if(event.key.keysym.sym==SDLK_w){
    }   
    if(event.key.keysym.sym==SDLK_s){
    }
    if(event.key.keysym.sym==SDLK_d){
    }
    if(event.key.keysym.sym==SDLK_a){
    }
}

void Gui::onMouseClick(SDL_Event event, bool& run){
    log("Mouse button clicked [menu]");
    int mousex, mousey;
    SDL_GetMouseState(&mousex,&mousey);
    for(auto& b: buttons){
        int w=b.texture.textureRectangle->w;
        int h=b.texture.textureRectangle->h;
        int x=b.texture.textureRectangle->x;
        int y=b.texture.textureRectangle->y;
        if(mousex >=x && mousex <=x+w && mousey >=y && mousey<=y+h){
            b.defaultButtonOnClick(event);
        }
    }
}

void Gui::onMouseRelease(SDL_Event event, bool& run){
    log("Mouse button released [menu]");
    int mousex, mousey;
    SDL_GetMouseState(&mousex,&mousey);
    for(auto& b: buttons){
        int w=b.texture.textureRectangle->w;
        int h=b.texture.textureRectangle->h;
        int x=b.texture.textureRectangle->x;
        int y=b.texture.textureRectangle->y;
        if(mousex >=x && mousex <=x+w && mousey >=y && mousey<=y+h){
            b.defaultButtonOnRelease(event);
        }
    }
}

void Gui::onMouseScroll(SDL_Event event, bool& run){

}

void Button::defaultButtonOnClick(SDL_Event event){
    log("Button is being pressed");
}

void Button::defaultButtonOnRelease(SDL_Event event){
    log("Button is being released");
}


bool Button::initButton(const char* label, const char* src, SDL_Rect* parentRect, void (*onClickHandler)(SDL_Event event),void (*onReleaseHandler)(SDL_Event event), int x, int y, int w, int h){
    if(this->texture.initTexture(src)==false){
        logErr("couldn't initialise a texture");
        return false;
    }
    this->label=textureWithText(label, SDL_Color{255,255,255,0});
    this->onClickHandler=onClickHandler;
    if(this->onClickHandler==nullptr){
        logErr("onClickHandler is nullptr");
    }
    this->onReleaseHandler=onReleaseHandler;
    if(this->onReleaseHandler==nullptr){
        logErr("onReleaseHandler is nullptr");
    }
    this->parentRect=parentRect;
    this->texture.textureRectangle->w=w;
    this->texture.textureRectangle->h=h;
    this->texture.textureRectangle->x=x+w;
    this->texture.textureRectangle->y=y+h;

    return true;
}

void Button::renderButton(){
    SDL_RenderCopy(global.renderer, texture.textureTexture, parentRect, texture.textureRectangle);
}
