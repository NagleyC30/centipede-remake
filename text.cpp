#include "text.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Constructor
Text::Text(float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), "assets/title.png", x, y, w, h);
	rect = spriteComponent->getRect();
}
