#ifndef		__HPP_CENTIPEDE__
#define		__HPP_CENTIPEDE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Centipede : public GameObject {
	public:
		Centipede(float x, float y);

        // What methods do we need?
		void up();
		void down();
		void left();
		void right();
		void update(float) override;
		bool willCollide(float, float);
	private:
		SDL_FRect* rect;
		float pps = 0.5;
		int xDir = 1; // stores whether centipede moves left or right
		int yDir = 1; // stores whether centipede moves up or down
};

#endif
