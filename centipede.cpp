#include "centipede.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "utility_functions.hpp"
#include <typeinfo>
#include <SDL3/SDL.h>

// Constructor
Centipede::Centipede(float x, float y){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/centipede.png", x, y);
	rect = spriteComponent->getRect();
}

// getter for xDir
int Centipede::getxDir() {
	return xDir;
}

// Called once per frame
void Centipede::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);

	// move based on OOB amd detected collisions
	if (rect->x + pps * deltaTime * xDir < 0 || rect->x + pps * deltaTime * xDir > WINDOW_WIDTH - CELL_SIZE
		|| willCollide(pps * deltaTime * xDir, 0.0)) {
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
	// GameObject* collisionObj = Engine::instance().scene->collision(&moveRect, this);
	
	// no collision if object is another centipede moving the same direction
	// (pretty sure I shouldn't need this but collision is being dumb, whoever implemented it must have no idea what they're doing)
	// if (Centipede* c = dynamic_cast<Centipede*>(collisionObj)) {
	// 	if (c->getxDir() == xDir) return false;
	// }
	return Engine::instance().scene->collision(&moveRect, this);
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Centipede::xMove(float deltaTime){
	rect->x += pps * deltaTime * xDir;
}

void Centipede::down(float deltaTime){
	rect->y += CELL_SIZE;
}
