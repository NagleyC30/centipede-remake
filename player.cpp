#include "player.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "projectile.hpp"
#include <SDL3/SDL.h>

// Constructor
Player::Player(float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/player.png", x, y, w, h);
	rect = spriteComponent->getRect();

}

// Called once per frame
void Player::update(float deltaTime) {
    GameObject::update(deltaTime);
    
    timeSinceLastShoot += deltaTime;
    timeSinceLastMove += deltaTime;

    // Poll held keys so holding a key keeps moving/shooting.
    const bool* keys = SDL_GetKeyboardState(nullptr);

    if (timeSinceLastMove >= moveCooldown) {
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
            left();
            timeSinceLastMove = 0.0;
        } else if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
            right();
            timeSinceLastMove = 0.0;
        }
    }

    if ((keys[SDL_SCANCODE_J] || keys[SDL_SCANCODE_SPACE]) && timeSinceLastShoot > shootCooldown) {
        shoot();
        timeSinceLastShoot = 0.0;
    }

    // if player death
    if (Engine::instance().scene->collision(rect, this)) {
        onDeath();
    }
}

static std::function<void()> onDeathCallback;

void Player::setOnDeathCallback(std::function<void()> callback) {
	onDeathCallback = callback;
}

void Player::onDeath() {
    Engine::instance().scene->markRemoval(this);
    if (onDeathCallback) onDeathCallback();
}

// Movement should be based on the time that has passed
// for smoothest motion.

// spawns projectile object one tile above player object
void Player::shoot() {
    Engine::instance().scene->markAdd(std::make_unique<Projectile>(rect->x, rect->y - CELL_SIZE));
}

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
