#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "projectile.hpp"
#include <SDL3/SDL.h>

// Constructor
Projectile::Projectile(float x, float y, float w, float h) {
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/projectile.png", x, y, w, h);
	rect = spriteComponent->getRect();
}

// Called once per frame
void Projectile::update(float deltaTime) {
    GameObject::update(deltaTime);

    if (rect->y - pps * deltaTime >= 0) {
        rect->y -= pps * deltaTime;

        // Check for collision
        GameObject* hitObj = Engine::instance().scene->collision(rect, this);
        if (hitObj) {
            Engine::instance().scene->markRemoval(hitObj);
            Engine::instance().scene->markRemoval(this);
            // delete this;
        }
    }

    // remove from scene and destroy object if OOB
    else {
        Engine::instance().scene->markRemoval(this);
        // delete this;
    }
}
