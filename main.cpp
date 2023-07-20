#include "src/engine/Engine.hpp"
#include "src/engine/globals.hpp"

void initGlobals(){
    global.menuHeight=700;
    global.menuWidth=1100;

    global.windowHeight=800;
    global.windowWidth=1200;
}

int main(){
    initGlobals();
    Engine engine;
    

    engine.mainLoop();
        
    return 0;
}