#include "../../src/game/objectHandler.hpp"

// SEARCHING SECTION //
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
void ObjectHandler::searchIfVesselClicked(int x, int y)
{
    vesselFoundId = 0;
    for(auto& h : vessels)
    {
        float AP = DistanceBetweenPoints(h.GetVesselRectangle().A,{x,y}), 
        BP = DistanceBetweenPoints(h.GetVesselRectangle().B,{x,y}),
        DP = DistanceBetweenPoints(h.GetVesselRectangle().D,{x,y});
        float scalarProduct1 = AP*(BP-2500-(AP*AP))/(-2*AP);
        float scalarProduct2 = AP*(DP-10000-(AP*AP))/(-2*AP);
        if(scalarProduct1>0 && scalarProduct1<2500 && scalarProduct2>0 && scalarProduct2<10000)
        {
            return;
        }
        vesselFoundId++;
    }
    vesselFoundId=-1;
    return;

}
bool ObjectHandler::isObjectClicked(int mouseX, int mouseY)
{
    thread planetCalc([=] {searchIfPlanetClicked(mouseX,mouseY);});
    thread vesselCalc([=] {searchIfVesselClicked(mouseX,mouseY);});
    planetCalc.join();
    vesselCalc.join();
    logOK("Mouse position : " ); std::cout<<mouseX<<" "<<mouseY<<endl;
    if(planetFoundId==-1)
    {
        log("Planet isn't clicked.");
        for(auto& k : planets)
        {
            if(k.getFlagState(1))k.modifyFlags(1);
            log("Flag modified");
        }
    }
    else if(planetFoundId>=0)
    {
        log("Planet clicked.");
        planets[planetFoundId].modifyFlags(1);
        return 1;
    }
    if(vesselFoundId==-1)
    {
        log("Vessel isn't clicked.");
        for(auto& k : vessels)
        {
            if(k.GetFlagState(1)) k.ModifyFlags(1);
            log("Flag modified");
        }
    }
    else if(planetFoundId>=0)
    {
        log("Vessel clicked.");
        vessels[vesselFoundId].ModifyFlags(1);
        return 1;
    }
    return 0;
}

// MOVEMENT SECTION //

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
                k.modifyFlags(5);
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
    for(auto& k : planetsMovementList)
    {
        float se ,dx ,dy;
        se = DistanceBetweenPoints({k.first.getPosition().x,k.first.getPosition().y},{k.second.x,k.second.y});
        dx = -k.first.getPosition().x+k.second.x;
        dy = -k.first.getPosition().y+k.second.y;
        if(k.first.getFlagState(5) && !PlanetCollisionCheck(k,se,dx,dy))
        {
            if(se<=k.first.getVelocity())
            {
                k.first.setPosition(k.second.x,k.second.y);
                k.first.modifyFlags(4);
                k.first.modifyFlags(5);
                logOK("Got there");
            }
            else
            {
                float xMod = ((dx/se)*k.first.getVelocity()), yMod = ((dy/se)*k.first.getVelocity());
                k.first.modifyPosition(xMod,yMod);
            }
        }
    }
    vector<pair<Planet&, vec2>> tmp;
    for(auto& d : planetsMovementList)
    {
        if(d.first.getFlagState(5))
        {
            tmp.push_back(d);
        }
    }
    planetsMovementList.swap(tmp);
    tmp.clear();
}

// VARIABLES HANDLING FUNCTIONS //

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

// COLLISIONS //

bool ObjectHandler::PlanetCollisionCheck(pair<Planet&,vec2> k, float& se, float& dx, float& dy)
{
    float x = ((dx/se)*k.first.getVelocity()), y = ((dy/se)*k.first.getVelocity());
    x += k.first.getPosition().x;
    y += k.first.getPosition().y;
    for(auto& p : planets)
    {
        auto d = DistanceBetweenPoints({x,y}, p.getPosition());
        if(d <= p.getRadius() + k.first.getRadius() && !(p == k.first))
        {
            return true;
        }
    }
    return false;
}