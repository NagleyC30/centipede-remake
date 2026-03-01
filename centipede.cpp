#include "centipede.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "utility_functions.hpp"
#include <SDL3/SDL.h>

// Constructor
Centipede::Centipede(float x, float y){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/centipede.png", x, y);
	rect = spriteComponent->getRect();
}

// Called once per frame
void Centipede::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);

	// move based on detected collisions and OOB
	if (rect->x + pps * deltaTime * xDir < 0 || rect->x + pps * deltaTime * xDir > WINDOW_WIDTH - CELL_SIZE || willCollide(pps * deltaTime * xDir, 0.0)) {
		down(deltaTime);
		xDir *= -1;
	}
	else {
		xMove(deltaTime);
	}
}

// Checks for "predictive" collisions, i.e. if a collision will occur given a movement
bool Centipede::willCollide(float dx, float dy) {
	SDL_FRect moveRect = *rect;
	moveRect.x += dx;
	moveRect.y += dy;
	return Engine::instance().scene->collision(this) != nullptr;
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Centipede::xMove(float deltaTime){
	rect->x += pps * deltaTime * xDir;
}

void Centipede::down(float deltaTime){
	rect->y += CELL_SIZE;
}
