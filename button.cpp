#include "button.hpp"
#include "engine.hpp"
#include "ui.hpp"
#include <SDL3/SDL.h>

// Constructor
Button::Button(const char* label, float x, float y, float w, float h)
	: label(label), rect{x, y, w, h} {}

void Button::setCallback(std::function<void()> callback) {
	onActivate = callback;
}

// Called once per frame
void Button::update(float deltaTime) {
	GameObject::update(deltaTime);
	SDL_Renderer* renderer = Engine::instance().getRenderer();

	// The mouse position is in window pixels; convert to the game's logical
	// coordinates (the window is scaled/letterboxed, e.g. in fullscreen).
	float windowX, windowY, mx, my;
	SDL_MouseButtonFlags buttons = SDL_GetMouseState(&windowX, &windowY);
	SDL_RenderCoordinatesFromWindow(renderer, windowX, windowY, &mx, &my);

	bool inside = mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
	bool mouseDown = buttons & SDL_BUTTON_LMASK;

	// Click = press and release both inside the button.
	bool activated = false;
	if (mouseDown && !wasMouseDown && inside) armed = true;
	if (!mouseDown) {
		if (armed && inside) activated = true;
		armed = false;
	}
	wasMouseDown = mouseDown;

	// Keyboard shortcut
	for (const SDL_Event& e : Engine::keyEvents) {
		if (e.key.scancode == SDL_SCANCODE_SPACE || e.key.scancode == SDL_SCANCODE_RETURN) {
			activated = true;
			break;
		}
	}

	// Draw: drop shadow, body (darker when pressed, lighter on hover), border, label.
	bool pressed = armed && inside;
	SDL_Color body = pressed ? SDL_Color{30, 100, 50, 255}
	                         : inside ? SDL_Color{70, 190, 100, 255} : SDL_Color{40, 150, 75, 255};
	SDL_Color border = inside ? SDL_Color{255, 255, 255, 255} : SDL_Color{170, 240, 190, 255};
	float offset = pressed ? 2.0f : 0.0f;

	UI::fillRect(renderer, {rect.x + 4, rect.y + 4, rect.w, rect.h}, {0, 0, 0, 140});
	SDL_FRect drawRect = {rect.x + offset, rect.y + offset, rect.w, rect.h};
	UI::fillRect(renderer, drawRect, body);
	UI::strokeRect(renderer, drawRect, border);
	const float labelScale = 3.0f;
	UI::drawTextCentered(renderer, label, drawRect.x + drawRect.w / 2,
		drawRect.y + (drawRect.h - 8 * labelScale) / 2, labelScale, {245, 255, 245, 255});

	// Run the callback last: it may switch scenes.
	if (activated && onActivate) onActivate();
}
