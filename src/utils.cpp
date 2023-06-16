#include "utils.hpp"



vec2 multiply(const matrix22& m, const vec2& v){
    return vec2{m.a*v.x+m.b*v.y, m.c*v.x + m.d*v.y};
}

void drawSquare(SDL_Renderer* renderer, int x, int y, int r){
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    for(int i=x-r;i<x+r;i++){
        for(int j=y-r;j<y+r;j++){
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);

}
