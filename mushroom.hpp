#ifndef		__HPP_MUSHROOM__
#define		__HPP_MUSHROOM__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Mushroom : public GameObject {
	public:
		Mushroom(float x = 0, float y = 0, float w = 32.0f, float h = 32.0f);
		void onHit();
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		SpriteComponent* sprite;
		float pps = 10.0;
		int hp = 3;
};


#endif
