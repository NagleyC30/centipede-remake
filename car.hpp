#ifndef		__HPP_CAR__
#define		__HPP_CAR__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Car : public GameObject {
	public:
		Car();
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
