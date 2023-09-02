#include "objects.hpp"

Object::Object(Texture& objTxt, rectangle objRect) : objectTexture(objTxt)
{
    objectRectangle = objRect;
}

void Object::modifyPosition(vec2 newPos)
{
    objectRectangle.position.x += newPos.x;
    objectRectangle.position.y += newPos.y;
    return;
}
void Object::setPosition(vec2 newPos)
{
    objectRectangle.position = newPos;
    return;
}
Texture& Object::GetObjectTexture()
{
    return objectTexture;
}
float Object::GetAngle()
{
    return rotation;
}
rectangle Object::GetObjectRect()
{
    return objectRectangle;
}
int Object::GetObjectID()
{
    return objectId;
}
void Object::ModifyAngle(float modifier)
{
    rotation+=modifier;
    return;
}