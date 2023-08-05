#include "../../src/game/objectHandler.hpp"

void ObjectHandler::searchIfPlanetClicked(int x, int y)
{
    int distance = 0;
    planetFoundId=0;
    for(auto& k : planets)
    {
        distance = pow((x-k.getPosition().x),2)+pow((y-k.getPosition().y),2);
        if(distance<pow(k.getRadius(),2))
        {
            return;
        }
        planetFoundId++;
    }
    planetFoundId=-1;
    return;
}
bool ObjectHandler::isObjectClicked(int mouseX, int mouseY)
{
    thread planetCalc([=] {searchIfPlanetClicked(mouseX,mouseY);});
    planetCalc.join();
    if(planetFoundId==-1)
    {
        log("Planet isn't clicked.");
        for(auto& k : planets)
        {
            k.modifyFlags(1);
            log("Flag modified");
        }
    }
    else if(planetFoundId>=0)
    {
        log("Planet clicked.");
        planets[planetFoundId].modifyFlags(1);
        return 1;
    }
    return 0;
}
void ObjectHandler::addToMovementList(int point_x, int point_y)
{
    for(auto& k : planets)
    {
        if(k.getFlagState(1))
        {
            if(!k.getFlagState(4))
            {
                log("Added to movement list");
                k.modifyFlags(4);
                vec2 x = {point_x,point_y};
                planetsMovementList.push_back({k,x});
            }
            else 
            {
                for(auto& h : planetsMovementList)
                {
                    if(k == h.first)
                    {
                        h.second = {(float)point_x,(float)point_y};
                        logOK("Changed move order");
                    }
                }
            }
        }
        
    }
}
void ObjectHandler::moveObjects()
{
    uint8_t id = 0;
    vector<uint8_t> ids;
    for(auto& k : planetsMovementList)
    {
        if((pow(k.first.getPosition().x-k.second.x,2)+pow(k.first.getPosition().y-k.second.y,2))<=pow(k.first.getVelocity(),2))
        {
            k.first.setPosition(k.second.x,k.second.y);
            ids.push_back(id);
            logOK("Got there");
        }
        else
        {
            float angle = atan((k.first.getPosition().x-k.second.x)/(k.first.getPosition().y-k.second.y));
            float xMod = (cos(angle)*k.first.getVelocity()), yMod = (sin(angle)*k.first.getVelocity());
            k.first.modifyPosition(xMod,yMod);
        }
        id++;
    }
    for(int i = 0; i<ids.size();i++)
    {
        planetsMovementList.erase(planetsMovementList.begin()+id);
        logOK("Object erased.");
    }
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
    planetFoundId=0;
    logOK("ObjectHandler created correctly.");
}
void ObjectHandler::addTexture(const char* src)
{
    Texture txt;
    txt.initTexture(src);
    txt.loadTexture(src);
    textures.push_back(txt);
}