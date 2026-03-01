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
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "centipede.png", x, y);
	rect = spriteComponent->getRect();
}

// Called once per frame
void Centipede::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);

	// move based on detected collisions and OOB
	if (rect->x + pps * deltaTime * xDir < 0 || rect->x + pps * deltaTime * xDir > WINDOW_WIDTH - CELL_SIZE || willCollide(pps * deltaTime * xDir, 0.0)) {
		rect->y += CELL_SIZE;
		xDir *= -1;
	}
	else {
		rect->x += pps * deltaTime * xDir;
	}
}

// Checks for "predictive" collisions, i.e. if a collision will occur given a movement
bool Centipede::willCollide(float dx, float dy) {
	SDL_FRect moveRect = *rect;
	moveRect.x += dx;
	moveRect.y += dy;
	return Engine::instance().scene->collision(moveRect, this) != nullptr;
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Centipede::up(){
	rect->y -= CELL_SIZE;
}

void Centipede::down(){
	rect->y += CELL_SIZE;
}

void Centipede::left(){
	rect->x -= CELL_SIZE;
}

void Centipede::right(){
	rect->x += CELL_SIZE;
}
