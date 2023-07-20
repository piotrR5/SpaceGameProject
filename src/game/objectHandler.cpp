#include "objectHandler.hpp"

void ObjectHandler::searchIfPlanetClicked(int x, int y, int& id)
{
    int distance = 0;
    for(auto& k : planets)
    {
        distance = pow((x-k.getPosition().first),2)+pow((y-k.getPosition().second),2);
        if(distance<pow(k.getRadius(),2))
        {
            return;
        }
        id++;
    }
    id=-1;
    return;
}
bool ObjectHandler::isObjectClicked(int mouseX, int mouseY)
{
    static int planetFoundId = 0;
    thread planetCalc([=] {searchIfPlanetClicked(mouseX,mouseY,planetFoundId);});
    planetCalc.join();
    if(planetFoundId==-1)
    {
        log("Planet isn't clicked.");
    }
    else if(planetFoundId>=0)
    {
        log("Planet clicked.");
        planets[planetFoundId].modifyFlags(1);
        return 1;
    }
    return 0;
}
void ObjectHandler::addPlanet(Planet p)
{
    planets.push_back(p);
    log("Planet added to vector");
}
void ObjectHandler::addVessel(Vessel v)
{
    vessels.push_back(v);
    log("Vessel added to vector");
}
ObjectHandler::ObjectHandler()
{
    planets.clear();
    vessels.clear();
    logOK("ObjectHandler created correctly.");
}
void ObjectHandler::addTexture(const char* src)
{
    Texture txt;
    txt.initTexture(src);
    txt.loadTexture(src);
    textures.push_back(txt);
}