#ifndef OBJECT_HANDLER
#define OBJECT_HANDLER


#include <vector>
#include <thread>
#include <cmath>
#include <iostream>
#include "entity-planet.hpp"
#include "entity-vessel.hpp"
#include "entity-projectile.hpp"
#include "../../src/engine/utils/log.hpp"

class ObjectHandler
{
    public :
    const uint8_t maxRotationAngle = 1;

    vector<Planet> planets;
    vector<Vessel> vessels;
    vector<Texture> textures;
    vector<pair<Planet&,vec2>> planetsMovementList;
    vector<tuple<Vessel&,vec2,float>> vesselMovementList;

    int planetFoundId;
    int vesselFoundId;

    void searchIfPlanetClicked(int x, int y);
    void searchIfVesselClicked(int x, int y);
    bool isObjectClicked(int mouseX, int mouseY);

    void addToMovementList(int point_x, int point_y);
    void MoveVessels();
    void MoveObjects();
    void MovePlanets();

    void addPlanet(Planet p);
    void addVessel(Vessel v);
    void addTexture(const char* src);

    bool PlanetCollisionCheck(pair<Planet&, vec2>, float& se, float& dx, float& dy);
    bool VesselCollisionCheck(); //TODO

    ObjectHandler();
};
#endif