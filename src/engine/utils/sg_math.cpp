#include "../utils/sg_math.hpp"

vec2 vec2::AddVec2(vec2 a, vec2 b)
{
    vec2 ret;
    ret.x = a.x+b.x;
    ret.y = a.y+b.y;
    return ret;
}
float DistanceBetweenPoints(vec2 start, vec2 end)
{
    return sqrt(pow(start.x-end.x,2)+pow(start.y-end.y,2));
}
rectangle RotateRect(rectangle InputRectangle, float angle)
{
    rectangle Rect;
    Rect.A = {InputRectangle.A.x*cos(angle) - InputRectangle.A.y*sin(angle),InputRectangle.A.y*cos(angle) + InputRectangle.A.x*sin(angle)};
    Rect.B = {InputRectangle.B.x*cos(angle) - InputRectangle.B.y*sin(angle),InputRectangle.B.y*cos(angle) + InputRectangle.B.y*sin(angle)};
    Rect.C = {InputRectangle.C.x*cos(angle) - InputRectangle.C.y*sin(angle),InputRectangle.C.y*cos(angle) + InputRectangle.C.y*sin(angle)};
    Rect.D = {InputRectangle.D.x*cos(angle) - InputRectangle.D.y*sin(angle),InputRectangle.D.y*cos(angle) + InputRectangle.D.y*sin(angle)};
    return Rect;
}
float FindRotationAngle(vec2 mousePos, rectangle Rect)
{
    vec2 abCenter = {(Rect.A.x+Rect.B.x)/2,(Rect.A.y+Rect.B.y)/2};
    float a1,b1,a2,b2,d,alpha;
    a1 = (abCenter.y-Rect.position.y)/(abCenter.x-Rect.position.x);
    b1 = abCenter.y - a1*abCenter.x;
    a2 = (mousePos.y-Rect.position.y)/(mousePos.x-Rect.position.x);
    b2 = mousePos.y-a2*mousePos.x;
    d = abs(a1*mousePos.x - mousePos.y + b1)/sqrt(a1*a1 + 1);
    alpha = asin(d/DistanceBetweenPoints(mousePos,Rect.position));
    if(alpha < 180) return alpha;
    else return -(360-alpha);
}
rectangle GenerateBasicRect()
{
    return {{0,0},{-50,50},{50,50},{50,-50},{-50,-50}};
}