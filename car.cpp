#include "car.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Constructor
Car::Car(){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprite.png");
	rect = spriteComponent->getRect();

}

// Called once per frame
void Car::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);
	for(auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it){
		if(it->key.key == SDLK_W){
			up(deltaTime);
		}
		if(it->key.key == SDLK_S){
			down(deltaTime);
		}
		if(it->key.key == SDLK_A){
			left(deltaTime);
		}
		if(it->key.key == SDLK_D){
			right(deltaTime);
		}
	}
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Car::up(float dt){
	rect->y -= pps * dt;
}

void Car::down(float dt){
	rect->y += pps * dt;
}

void Car::left(float dt){
	rect->x -= pps * dt;
}

void Car::right(float dt){
	rect->x += pps * dt;
}
