#ifndef OBJECT_HANDLER
#define OBJECT_HANDLER


#include <vector>
#include <thread>
#include <cmath>
#include "entity-planet.hpp"
#include "entity-vessel.hpp"
#include "entity-projectile.hpp"
#include "../engine/utils/log.hpp"

class ObjectHandler
{
    public :
    vector<Planet> planets;
    vector<Vessel> vessels;
    vector<Texture> textures;
    void searchIfPlanetClicked(int x, int y, int& id);
    bool isObjectClicked(int mouseX, int mouseY);
    void addPlanet(Planet p);
    void addVessel(Vessel v);
    void addTexture(const char* src);

    ObjectHandler();
};
#endif