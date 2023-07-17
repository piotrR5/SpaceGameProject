#ifndef OBJECT_HANDLER
#define OBJECT_HANDLER


#include <vector>
#include <thread>
#include <cmath>
#include "entity-planet.hpp"
#include "entity-vessel.hpp"
#include "entity-projectile.hpp"
#include "../../src/engine/utils/log.hpp"

class ObjectHandler
{
    private :
    std::vector<Planet> planets;
    std::vector<Vessel> vessels;
    public :
    void searchIfPlanetClicked(int x, int y, int& id);
    bool isObjectClicked(int mouseX, int mouseY);
    void addObject(auto& object);

    ObjectHandler();
};
#endif