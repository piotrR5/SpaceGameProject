#ifndef OBJECTS
#define OBJECTS

#include "../engine/rendering/texture.hpp"
#include "../engine/utils/sg_math.hpp"

class Object
{
    protected :
    Texture& objectTexture;
    rectangle objectRectangle;
    int objectId;
    float rotation;
    public :
    Object(Texture& objTxt, rectangle objRect);
    void modifyPosition(vec2 newPos);
    void setPosition(vec2 newPos);
    Texture& GetObjectTexture();
    float GetAngle();
    void ModifyAngle(float modifier);
    rectangle GetObjectRect();
    int GetObjectID();
};
#endif