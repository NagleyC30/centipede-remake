#ifndef		__HPP_CENTIPEDE__
#define		__HPP_CENTIPEDE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Centipede : public GameObject {
	public:
		Centipede();

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
