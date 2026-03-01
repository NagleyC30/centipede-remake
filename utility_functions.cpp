#include "utility_functions.hpp"

bool UtilityFunctions::AABB_Collision(const SDL_FRect& a, const SDL_FRect& b)
{
    // if ((r1.x + r1.w < r2.x) ||
    //     (r1.x > r2.x + r2.w) ||
    //     (r1.y + r1.h < r2.y) ||
    //     (r1.y > r2.y + r2.h)) {
    //     return false;
    // }

    // return true;

    if ((a.x < b.x + b.w) && (b.x < a.x + a.w)) { // Check for collision on x axis
        if ((a.y < b.y + b.h) && (b.y < a.y + a.h)) { // Check for collision on y axis
            return true;
        }
    }
    return false; // No collision
}


