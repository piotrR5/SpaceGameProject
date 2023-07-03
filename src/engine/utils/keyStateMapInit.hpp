#ifndef KEY_STATE_MAP_INIT

#define KEY_STATE_MAP_INIT

#include <SDL2/SDL.h>
#include <map>

std::map<SDL_Keycode, bool>initKeyStateMap();

bool setState(std::map<SDL_Keycode, bool>&keyMap, SDL_Keycode, bool);

#endif