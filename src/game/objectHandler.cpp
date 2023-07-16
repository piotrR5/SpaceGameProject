#include "../../src/game/objectHandler.hpp"

vector<Planet> planets;
vector<Vessel> vessels;

void searchIfPlanetClicked(int x, int y, int& id)
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
bool isObjectClicked(int mouseX, int mouseY)
{
    int planetFoundId = 0;
    thread planetCalc(searchIfPlanetClicked,mouseX,mouseY,std::ref(planetFoundId));
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
