#include "button.hpp"
#include "engine.hpp"
#include "mushroom.hpp"
#include "player.hpp"
#include "centipede.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>
#include <random>

// Constructor
Button::Button(float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/buttonV2.png", x, y, w, h);
	rect = spriteComponent->getRect();
	onSpacebarClick = nullptr;
}

// Called once per frame
void Button::setCallback(std::function<void()> callback) {
	onSpacebarClick = callback;
}

void Button::update(float deltaTime) {
	GameObject::update(deltaTime);
	for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		if (it->key.key == SDLK_SPACE) {
			if (onSpacebarClick) onSpacebarClick();
			break;
		}
	}
}