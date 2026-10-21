#include "components.hpp"
#include "game_objects.hpp"
#include "engine.hpp"

#include <glm/vec4.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

GameObject* Component::getOwner() const {
    return owner;
}

void Component::setOwner(GameObject* go) {
    owner = go;
}

void SpriteComponent::setX(int x) {
    destRect.x = x;
}

void SpriteComponent::setY(int y) {
    destRect.y = y;
}

bool SpriteComponent::loadSprite(SDL_Renderer* renderer, const char* path, float x, float y, float w, float h) {
    destRect = {x, y, w, h};
    this->renderer = renderer;

    // The engine caches textures, so each image is only loaded from disk once.
    sprite = Engine::instance().getTexture(path);

    return sprite != nullptr;
}

// Sometimes we might need to get the image.
SDL_Texture* SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::setTint(Uint8 r, Uint8 g, Uint8 b) {
    tintR = r;
    tintG = g;
    tintB = b;
}

void SpriteComponent::update(float) {
    if (!sprite) return;
    // The texture is shared, so apply this sprite's tint right before drawing.
    SDL_SetTextureColorMod(sprite, tintR, tintG, tintB);
    SDL_RenderTexture(renderer, sprite, nullptr, &destRect);
}

// The destRect is where and how much of the image will be drawn.
SDL_FRect* SpriteComponent::getRect(){
    return &destRect;
}

void TransformComponent::update(float) {
    // empty for now
}
