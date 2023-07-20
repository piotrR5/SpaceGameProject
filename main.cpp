#include "src/engine/Engine.hpp"
#include "src/engine/globals.hpp"

void initGlobals(){
    Globals::instance().menuHeight=700;
    Globals::instance().menuWidth=1100;

    Globals::instance().windowHeight=800;
    Globals::instance().windowWidth=1200;
}

int main(){
    Engine engine;
    initGlobals();

    engine.mainLoop();
        
    return 0;
}