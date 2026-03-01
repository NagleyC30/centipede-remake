#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "projectile.hpp"
#include <SDL3/SDL.h>

// Constructor
Projectile::Projectile(float x, float y) {
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "projectile.png", x, y);
	rect = spriteComponent->getRect();
}

// Called once per frame
void Projectile::update(float deltaTime) {
    GameObject::update(deltaTime);
    
    if (rect->y - pps * deltaTime >= 0) {
        rect->y -= pps * deltaTime;
    }

    // remove from scene and destroy object if OOB
    else {
        Engine::instance().scene->markRemoval(this);
        delete this;
    }
}