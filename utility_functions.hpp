#ifndef __UTILITY_FUNCTIONS__
#define __UTILITY_FUNCTIONS__

#include <SDL3/SDL_rect.h>
#include "constants.hpp"

class UtilityFunctions {
    public: 
        static bool AABB_Collision(const SDL_FRect& r1, const SDL_FRect & r2);
        static float nearestTile(const float x);

        template <typename T>
        static T clamp(T value, T min, T max) {
            if (value < min) {
                return min; 
            }

            if (value > max) {
                return max; 
            }

            return value;
        }
};

#endif
