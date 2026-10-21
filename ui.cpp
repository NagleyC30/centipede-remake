#include "ui.hpp"
#include "engine.hpp"
#include "constants.hpp"
#include <cstring>

namespace UI {
	float textWidth(const char* text, float scale) {
		return std::strlen(text) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale;
	}

	void drawText(SDL_Renderer* r, const char* text, float x, float y, float scale, SDL_Color c) {
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
		// The debug font has a fixed size, so enlarge it by scaling the renderer.
		SDL_SetRenderScale(r, scale, scale);
		SDL_RenderDebugText(r, x / scale, y / scale, text);
		SDL_SetRenderScale(r, 1.0f, 1.0f);
	}

	void drawTextCentered(SDL_Renderer* r, const char* text, float cx, float y, float scale, SDL_Color c) {
		drawText(r, text, cx - textWidth(text, scale) / 2, y, scale, c);
	}

	void fillRect(SDL_Renderer* r, const SDL_FRect& rect, SDL_Color c) {
		SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(r, &rect);
		SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
	}

	void strokeRect(SDL_Renderer* r, const SDL_FRect& rect, SDL_Color c) {
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
		SDL_RenderRect(r, &rect);
	}
}

void MenuBackdrop::update(float deltaTime) {
	GameObject::update(deltaTime);
	SDL_Renderer* r = Engine::instance().getRenderer();

	// Fade from deep green at the top to black at the bottom, in 4px bands.
	const int band = 4;
	for (int y = 0; y < WINDOW_HEIGHT; y += band) {
		float t = static_cast<float>(y) / WINDOW_HEIGHT;
		SDL_Color c = {static_cast<Uint8>(14 * (1 - t)), static_cast<Uint8>(34 * (1 - t)), static_cast<Uint8>(20 * (1 - t)), 255};
		UI::fillRect(r, {0, static_cast<float>(y), WINDOW_WIDTH, static_cast<float>(band)}, c);
	}
}

RulesPanel::RulesPanel(float x, float y, float w, float h) : rect{x, y, w, h} {}

void RulesPanel::update(float deltaTime) {
	GameObject::update(deltaTime);
	SDL_Renderer* r = Engine::instance().getRenderer();

	const SDL_Color heading = {255, 220, 80, 255};
	const SDL_Color keyColor = {120, 230, 255, 255};
	const SDL_Color text = {225, 240, 225, 255};

	// Card with a translucent fill and a light border.
	UI::fillRect(r, rect, {10, 30, 18, 210});
	UI::strokeRect(r, rect, {90, 200, 120, 255});

	float y = rect.y + 14;
	UI::drawTextCentered(r, "HOW TO PLAY", rect.x + rect.w / 2, y, 3, heading);
	y += 38;

	// Controls: key column on the left, action on the right.
	struct Row { const char* keys; const char* action; };
	const Row controls[] = {
		{"A / D, Arrows", "Move"},
		{"J, Space", "Shoot"},
		{"F11", "Fullscreen"},
		{"Esc", "Quit"},
	};
	for (const Row& row : controls) {
		UI::drawText(r, row.keys, rect.x + 30, y, 2, keyColor);
		UI::drawText(r, row.action, rect.x + 330, y, 2, text);
		y += 20;
	}

	y += 6;
	UI::drawText(r, "Shoot all the centipede segments.", rect.x + 30, y, 2, text);
	y += 20;
	UI::drawText(r, "Mushrooms take 3 hits to clear.", rect.x + 30, y, 2, text);
	y += 20;
	UI::drawText(r, "Touching a centipede ends the run.", rect.x + 30, y, 2, text);
}

Label::Label(const char* text, float cx, float y, float scale, SDL_Color color)
	: text(text), cx(cx), y(y), scale(scale), color(color) {}

void Label::update(float deltaTime) {
	GameObject::update(deltaTime);
	UI::drawTextCentered(Engine::instance().getRenderer(), text, cx, y, scale, color);
}
