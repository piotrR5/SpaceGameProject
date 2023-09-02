#include "../../src/game/objectHandler.hpp"

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
                    if(k.GetObjectID() == h.first.GetObjectID())
                    {
                        h.second = {(float)point_x,(float)point_y};
                        logOK("Changed move order");
                    }
                }
            }
        }
        
    }
    for(auto& k : vessels)
    {
        if(k.GetFlagState(5))
        {
            if(!k.GetFlagState(3))
            {
                log("Added to movement list");
                k.ModifyFlags(3);
                k.ModifyFlags(4);
                vec2 x = {point_x,point_y};
                vesselMovementList.push_back({k,x,FindRotationAngle({(float)point_x,(float)point_y},k.GetVesselRectangle())});
            }
            else
            {
                for(auto& h : vesselMovementList)
                {
                    if(k.GetVesselId() == get<0>(h).GetVesselId())
                    {
                        get<1>(h) = {(float)point_x,(float)point_y};
                        get<2>(h) = FindRotationAngle({(float)point_x,(float)point_y},k.GetVesselRectangle());
                        logOK("Changed move order");
                    }
                }
            }
        }
    }
}
void ObjectHandler::MoveVessels()
{
    for(auto& k : vesselMovementList)
    {
        if(get<2>(k)==0)
        {
            float se ,dx ,dy;
            se = DistanceBetweenPoints(get<0>(k).GetVesselRectangle().position,get<1>(k));
            dx = -get<0>(k).GetVesselRectangle().position.x+get<1>(k).x;
            dy = -get<0>(k).GetVesselRectangle().position.y+get<1>(k).y;
            if(get<0>(k).GetFlagState(4))
            {
                if(se<=get<0>(k).GetVelocity())
                {
                    get<0>(k).ChangeRectangle({get<1>(k),get<0>(k).GetVesselRectangle().A,get<0>(k).GetVesselRectangle().B,
                    get<0>(k).GetVesselRectangle().C,get<0>(k).GetVesselRectangle().D});
                }
                else
                {
                    float xMod = ((dx/se)*get<0>(k).GetVelocity()), yMod = ((dy/se)*get<0>(k).GetVelocity());
                    get<0>(k).ChangeRectangle({{xMod,yMod},get<0>(k).GetVesselRectangle().A,get<0>(k).GetVesselRectangle().B,
                    get<0>(k).GetVesselRectangle().C,get<0>(k).GetVesselRectangle().D});
                }
            }
        }
        else if(get<2>(k)<=maxRotationAngle && get<2>(k)>=-maxRotationAngle)
        {
            get<0>(k).ChangeRectangle(RotateRect(get<0>(k).GetVesselRectangle(),get<2>(k)));
        }
        else if(get<2>(k)<0)
        {
            get<0>(k).ChangeRectangle(RotateRect(get<0>(k).GetVesselRectangle(),-maxRotationAngle));
        }
        else
        {
            get<0>(k).ChangeRectangle(RotateRect(get<0>(k).GetVesselRectangle(),maxRotationAngle));
        }
    }
}
void ObjectHandler::MovePlanets()
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
                k.first.setPosition({k.second.x,k.second.y});
                k.first.modifyFlags(4);
                k.first.modifyFlags(5);
                logOK("Got there");
            }
            else
            {
                float xMod = ((dx/se)*k.first.getVelocity()), yMod = ((dy/se)*k.first.getVelocity());
                k.first.modifyPosition({xMod,yMod});
            }
        }
    }
}
void ObjectHandler::MoveObjects()
{
    thread planetMove([=] {MovePlanets();});
    thread vesselMove([=] {MoveVessels();});
    planetMove.join();
    vesselMove.join();
    vector<pair<Planet&, vec2>> tmpPlanets;
    vector<tuple<Vessel&,vec2,float>> tmpVessels;
    for(auto& d : planetsMovementList)
    {
        if(d.first.getFlagState(5))
        {
            tmpPlanets.push_back(d);
        }
    }
    for(auto& o : vesselMovementList)
    {
        if(get<0>(o).GetFlagState(4))
        {
            tmpVessels.push_back(o);
        }
    }
    planetsMovementList.swap(tmpPlanets);
    vesselMovementList.swap(tmpVessels);
    tmpPlanets.clear();
    tmpVessels.clear();
}
