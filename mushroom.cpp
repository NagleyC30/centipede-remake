#include "mushroom.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Constructor
Mushroom::Mushroom(float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/mushroom.png", x, y, w, h);
	rect = spriteComponent->getRect();
}

void Mushroom::onHit() {
	hp--;
	if (hp <= 0) {
		Engine::instance().scene->markRemoval(this);
	}
}

// Called once per frame
void Mushroom::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);
}
