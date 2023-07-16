#ifndef OBJECT_HANDLER
#define OBJECT_HANDLER


#include <vector>
#include <thread>
#include <cmath>
#include "entity-planet.hpp"
#include "entity-vessel.hpp"
#include "entity-projectile.hpp"
#include "../../src/engine/utils/log.hpp"

void searchIfPlanetClicked(int x, int y, int& id);
bool isObjectClicked(int mouseX, int mouseY);

#endif