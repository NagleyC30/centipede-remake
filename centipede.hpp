#ifndef		__HPP_CENTIPEDE__
#define		__HPP_CENTIPEDE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Centipede : public GameObject {
	public:
		Centipede(float x, float y, float w = 32.0f, float h = 32.0f);

        // What methods do we need?
		void xMove(float);
		void down(float);
		void update(float) override;
		bool willCollide(float, float);
	private:
		SDL_FRect* rect;
		float pps = 0.5;
		int xDir = 1; // stores whether centipede moves left or right
};

#endif
