#ifndef		__HPP_PROJECTILE__
#define		__HPP_PROJECTILE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Projectile : public GameObject {
	public:
		Projectile(float x, float y);
        ~Projectile() = default;

        // What methods do we need?
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
};


#endif
