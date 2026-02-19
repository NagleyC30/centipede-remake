#include "UtilityFunctions.h"

bool UtilityFunctions::AABB_Collision(const SDL_FRect& r1, const SDL_FRect& r2)
{
    if ((r1.x + r1.w < r2.x) ||
        (r1.x > r2.x + r2.w) ||
        (r1.y + r1.h < r2.y) ||
        (r1.y > r2.y + r2.h)) {
        return false;
    }

    return true;
}


