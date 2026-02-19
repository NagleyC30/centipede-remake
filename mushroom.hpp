#ifndef		__HPP_MUSHROOM__
#define		__HPP_MUSHROOM__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Mushroom : public GameObject {
	public:
		Mushroom();

        // What methods do we need?
		void up(float);
		void down(float);
		void left(float);
		void right(float);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
};


#endif
