#include "player.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include <SDL3/SDL.h>

// Constructor
Player::Player(float x, float y){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "mushroom.png", x, y);
	rect = spriteComponent->getRect();

}

// Called once per frame
void Player::update(float deltaTime) {
    GameObject::update(deltaTime);

    for (auto it = Engine::keyEvents.begin(); 
        it != Engine::keyEvents.end(); ++it) {

        if (it->key.key == SDLK_A) {
			left();
        }

        if (it->key.key == SDLK_D) {
            right();
        }
    }
}

// Movement should be based on the time that has passed
// for smoothest motion.

void Player::left() {
    if (rect->x - CELL_SIZE >= 0) {
        rect->x -= CELL_SIZE;
    }
}

void Player::right() {
    if (rect->x + CELL_SIZE <= (NUM_COLS - 1) * CELL_SIZE) {
        rect->x += CELL_SIZE;
    }
}