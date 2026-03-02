#include "text.hpp"
#include "engine.hpp"

// Constructor
Text::Text(char* path, float x, float y, float w, float h){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(), path, x, y, w, h);
	rect = spriteComponent->getRect();
}
