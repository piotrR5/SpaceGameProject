#include "text.hpp"

bool initTTF_Font(const char* src){
    global.font=(TTF_OpenFont( src, 28 ));
    if( global.font == nullptr )
    {
        logErr("couldn't load font");
        return false;
    }
    return true;
}

Texture textureWithText(const char* label, SDL_Color color){
    SDL_Surface* textSurface = TTF_RenderText_Solid(global.font, label, color);

    SDL_Texture* texture;
    SDL_Rect* textRect=new SDL_Rect;
    Texture txt;
    
    if(textSurface == nullptr){
        logErr("unable to create surface");
        txt.initTexture("assets/missingTexture.png");
        return txt;
    }
    else{
        texture = SDL_CreateTextureFromSurface(global.renderer, textSurface);
        if( texture == NULL ){
            logErr("couldn't create texture");
            txt.loadTexture("assets/missingTexture.png");
            return txt;
        }
        else{
            //Get image dimensions
            textRect->w = textSurface->w;
            textRect->h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    
    txt.initTexture(texture, textRect);

    return txt;
}