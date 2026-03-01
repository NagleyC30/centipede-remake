#ifndef		__HPP_BUTTON__
#define		__HPP_BUTTON__

#include "game_objects.hpp"
#include "constants.hpp"
#include <SDL3/SDL.h>
#include <functional>

class Button : public GameObject {
	public:
		Button(float x = BUTTON_X, float y = BUTTON_Y, float w = BUTTON_WIDTH, float h = BUTTON_HEIGHT);
	    void update(float deltaTime) override;
    private:
		SDL_FRect* rect;
};


#endif
