#include "centipede.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "utility_functions.hpp"
#include "mushroom.hpp"
#include "player.hpp"
#include <SDL3/SDL.h>

static int centipedesAlive = 0;

// Constructor
Centipede::Centipede(float x, float y, float w, float h, float speedScale){
	pxPerMs *= speedScale;
	centipedesAlive++;
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/centipede.png", x, y, w, h);
	rect = spriteComponent->getRect();
}

Centipede::~Centipede() {
	centipedesAlive--;
}

int Centipede::aliveCount() {
	return centipedesAlive;
}

// getter for xDir
int Centipede::getxDir() {
	return xDir;
}

void Centipede::onHit() {
	Engine::instance().scene->markRemoval(this);

	// spawn mushroom on nearest tile
	// The scene takes ownership of the new mushroom (queued until end of frame)
	Engine::instance().scene->markAdd(std::make_unique<Mushroom>(UtilityFunctions::nearestTile(rect->x), rect->y));
}

// Called once per frame
void Centipede::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);

	// move based on OOB amd detected collisions
	if (rect->x + pxPerMs * deltaTime * xDir < 0 || rect->x + pxPerMs * deltaTime * xDir > WINDOW_WIDTH - CELL_SIZE
		|| willCollide(pxPerMs * deltaTime * xDir, 0.0)) {
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
	GameObject* collisionObj = Engine::instance().scene->collision(&moveRect, this);
	
	// no collision if object is another centipede moving the same direction
	// (pretty sure I shouldn't need this but collision is being dumb, whoever implemented it must have no idea what they're doing)
	// BAD, DON'T DO THIS
	if (Centipede* c = dynamic_cast<Centipede*>(collisionObj)) {
		return c->getxDir() != xDir;
	}
	if (Player* p = dynamic_cast<Player*>(collisionObj)) {
		return false;
	}
	return collisionObj;
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Centipede::xMove(float deltaTime){
	rect->x += pxPerMs * deltaTime * xDir;
}

void Centipede::down(float deltaTime){
	// Bounce between the bottom row and the top of the player zone instead of
	// walking off the bottom of the screen.
	const float bottomY = (NUM_ROWS - 1) * CELL_SIZE;
	const float zoneTopY = (NUM_ROWS - 6) * CELL_SIZE;
	if (yDir > 0 && rect->y >= bottomY) {
		yDir = -1;
	} else if (yDir < 0 && rect->y <= zoneTopY) {
		yDir = 1;
	}
	rect->y += CELL_SIZE * yDir;
	rect->x = UtilityFunctions::nearestTile(rect->x); // snap to nearest tile on x axis
}


void WaveSpawner::update(float deltaTime) {
	GameObject::update(deltaTime);

	// Segments still alive (removals are applied at end of frame, so a wave
	// counts as cleared on the frame after its last segment dies).
	if (Centipede::aliveCount() > 0) return;

	// Each wave is 25% faster than the last, capped at 3x.
	wave++;
	float speedScale = std::min(1.0f + 0.25f * (wave - 1), 3.0f);
	for (int i = 0; i < 12; i++) {
		Engine::instance().scene->markAdd(std::make_unique<Centipede>(
			NUM_COLS / 2 * CELL_SIZE - i * CELL_SIZE, 0, 32.0f, 32.0f, speedScale));
	}
}
