#ifndef __HPP_UI__
#define __HPP_UI__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Small helpers for drawing menu visuals with SDL primitives and SDL's
// built-in debug font (8x8 glyphs), so no font files are needed.
namespace UI {
	// Width in pixels of `text` at the given integer scale.
	float textWidth(const char* text, float scale);
	void drawText(SDL_Renderer* r, const char* text, float x, float y, float scale, SDL_Color c);
	// Draws text horizontally centred on cx.
	void drawTextCentered(SDL_Renderer* r, const char* text, float cx, float y, float scale, SDL_Color c);
	// Filled / outlined rectangles; fill honours the colour's alpha.
	void fillRect(SDL_Renderer* r, const SDL_FRect& rect, SDL_Color c);
	void strokeRect(SDL_Renderer* r, const SDL_FRect& rect, SDL_Color c);
}

// Dark vertical gradient drawn behind a menu screen.
class MenuBackdrop : public GameObject {
	public:
		void update(float deltaTime) override;
};

// "How to play" reference card shown on the title screen.
class RulesPanel : public GameObject {
	public:
		RulesPanel(float x, float y, float w, float h);
		void update(float deltaTime) override;
	private:
		SDL_FRect rect;
};

// A single line of centred text.
class Label : public GameObject {
	public:
		Label(const char* text, float cx, float y, float scale, SDL_Color color);
		void update(float deltaTime) override;
	private:
		const char* text;
		float cx, y, scale;
		SDL_Color color;
};

#endif
