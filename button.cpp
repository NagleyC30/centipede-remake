#include "button.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>

// Constructor
Button::Button(float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/button.png", x, y, w, h);
	rect = spriteComponent->getRect();
}

void Button::update(float deltaTime) {
    GameObject::update(deltaTime);
}
