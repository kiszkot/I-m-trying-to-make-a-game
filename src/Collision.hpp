#pragma once
#include <SDL2/SDL.h>
#include "ECS/ColliderComponent.hpp"

//class ColliderComponent;

class Collision {

public:

    static bool AABB(const SDL_Rect & rectA,  const SDL_Rect & rectB); //Axis Aligned Collision Box

    static bool AABB(const ColliderComponent & collA, const ColliderComponent & collB);

private:

};