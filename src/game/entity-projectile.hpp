#ifndef PROJECTILE
#define PROJECTILE

#include "../engine/utils/sg_math.hpp"
#include "../engine/rendering/texture.hpp"

struct Projectile
{
    vec2 velocity;
    Texture projectileTexture;

};
#endif