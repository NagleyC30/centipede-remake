#ifndef		__HPP_PLAYER__
#define		__HPP_PLAYER__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Player : public GameObject {
	public:
		Player(float x, float y, float w = 32.0f, float h = 32.0f);

        // What methods do we need?
		void onDeath();
		void shoot();
		void left();
		void right();
		void update(float deltaTime) override;

		static void setOnDeathCallback(std::function<void()> callback);
	private:
		SDL_FRect* rect;
		float shootCooldown = 250.0;
		float timeSinceLastShoot = 0.0;
};


#endif
