#ifndef		__HPP_PLAYER__
#define		__HPP_PLAYER__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Player : public GameObject {
	public:
		Player(float x, float y);

        // What methods do we need?
		void shoot();
		void left();
		void right();
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
};


#endif
