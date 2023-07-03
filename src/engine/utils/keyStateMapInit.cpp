#include "keyStateMapInit.hpp"

std::map<SDL_Keycode, bool>initKeyStateMap(){
    return {
        {
            SDLK_0, 0
        },
        {
            SDLK_1, 0
        },
        {
            SDLK_2, 0
        },
        {
            SDLK_3, 0
        },
        {
            SDLK_4, 0
        },
        {
            SDLK_5, 0
        },
        {
            SDLK_6, 0
        },
        {
            SDLK_7, 0
        },
        {
            SDLK_8, 0
        },
        {
            SDLK_9, 0
        },
        {
            SDLK_q, 0
        },
        {
            SDLK_w, 0
        },
        {
            SDLK_e, 0
        },
        {
            SDLK_r, 0
        },
        {
            SDLK_t, 0
        },
        {
            SDLK_y, 0
        },
        {
            SDLK_u, 0
        },
        {
            SDLK_i, 0
        },
        {
            SDLK_o, 0
        },
        {
            SDLK_p, 0
        },
        {
            SDLK_a, 0
        },
        {
            SDLK_s, 0
        },
        {
            SDLK_d, 0
        },
        {
            SDLK_f, 0
        },
        {
            SDLK_g, 0
        },
        {
            SDLK_h, 0
        },
        {
            SDLK_j, 0
        },
        {
            SDLK_k, 0
        },
        {
            SDLK_l, 0
        },
        {
            SDLK_z, 0
        },
        {
            SDLK_x, 0
        },
        {
            SDLK_c, 0
        },
        {
            SDLK_v, 0
        },
        {
            SDLK_b, 0
        },
        {
            SDLK_n, 0
        },
        {
            SDLK_m, 0
        },
        {
            SDLK_SPACE, 0
        },
        {
            SDLK_TAB, 0
        },
        {
            SDLK_LSHIFT, 0
        },
        {
            SDLK_LCTRL, 0
        },
        {
            SDLK_LALT, 0
        },
        {
            SDLK_RSHIFT, 0
        },
        {
            SDLK_RCTRL, 0
        },
        {
            SDLK_RALT, 0
        },
        {
            SDLK_HOME, 0
        },
        {
            SDLK_UP, 0
        },
        {
            SDLK_DOWN, 0
        },
        {
            SDLK_RIGHT, 0
        },
        {
            SDLK_LEFT, 0
        },
    };
}

bool setState(std::map<SDL_Keycode, bool>&keyMap, SDL_Keycode key, bool state){
    if(keyMap.find(key)!=keyMap.end()){
        if(keyMap[key]!=state){
            keyMap[key]=state;
            return true;
        }
        return true;
    }
    return false;
}