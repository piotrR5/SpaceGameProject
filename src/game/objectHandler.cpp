#include "../../src/game/objectHandler.hpp"

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
    int planetFoundId = 0;
    thread planetCalc([=] {searchIfPlanetClicked(mouseX,mouseY,&planetFoundId);});
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
void ObjectHandler::addObject(auto& object)
{
    switch(typeid(object))
    {
        case Planet :
        planets.push_back(object);
        log("Planet added to vector.");
        break;
        default : 
        logErr("Wrong object type !");
        break;
    }
}
ObjectHandler::ObjectHandler()
{
    planets.clear();
    vessels.clear();
    log("ObjectHandler created correctly.");
}
