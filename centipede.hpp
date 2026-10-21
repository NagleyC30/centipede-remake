#ifndef		__HPP_CENTIPEDE__
#define		__HPP_CENTIPEDE__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Centipede : public GameObject {
	public:
		Centipede(float x, float y, float w = 32.0f, float h = 32.0f, float speedScale = 1.0f);
		~Centipede();

		// Number of centipede segments currently alive (used to detect a cleared wave)
		static int aliveCount();

        // What methods do we need?
		int getxDir();
		void xMove(float);
		void down(float);
		void onHit();
		void update(float) override;
		bool willCollide(float, float);
	private:
		SDL_FRect* rect;
		float pps = 0.1;
		int xDir = 1; // stores whether centipede moves left or right
		int yDir = 1; // 1 = moving down the screen, -1 = moving back up
};

// Keeps the game going: spawns the first wave, and a new, faster wave
// every time the previous one is wiped out. Has no sprite.
class WaveSpawner : public GameObject {
	public:
		void update(float deltaTime) override;
	private:
		int wave = 0;
};

#endif
