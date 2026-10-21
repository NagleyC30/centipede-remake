#ifndef		__HPP_TEXT__
#define		__HPP_TEXT__

#include "game_objects.hpp"
#include "constants.hpp"
#include <SDL3/SDL.h>

class Text : public GameObject {
	public:
		Text(const char* path, float x = TITLE_X, float y = TITLE_Y, float w = TITLE_WIDTH, float h = TITLE_HEIGHT);
	private:
		SDL_FRect* rect;
};


#endif
