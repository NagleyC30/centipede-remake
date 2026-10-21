#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#include <functional>
#include <SDL3/SDL.h>
#include <unordered_map>

class GameObject;

class Component {
	public:
		// We want these to be abstract (virtual in c++)
		virtual ~Component() = default;
		virtual void update(float deltaTime) {}

		GameObject* getOwner() const;

	private:
		void setOwner(GameObject* go);

		// Make it easier to share information with GameObjects
		// by letting them see our private data.
		friend class GameObject;

		// To which game object do we belong?
		GameObject* owner = nullptr;
};

class SpriteComponent : public Component {
	public:
		void setX(float x);
		void setY(float y);
		// Load an image from a file.  Normally we would
		// probably have multiple images per sprite for
		// animations.
		bool loadSprite(SDL_Renderer* renderer, const char* path, float x, float y, float w, float h);
		SDL_Texture* getSprite();
		// Colour multiplier applied when drawing (255 = unchanged). Stored per
		// sprite, since the underlying texture is shared between objects.
		void setTint(Uint8 r, Uint8 g, Uint8 b);
		void update(float deltaTime) override;
		SDL_FRect* getRect();

	private:
		// For convenience we can keep track of the renderer
		// from the engine.
		SDL_Renderer* renderer = nullptr;
		SDL_FRect destRect{};
		// Shared with other sprites and owned by the Engine's texture cache
		SDL_Texture* sprite = nullptr;
		Uint8 tintR = 255, tintG = 255, tintB = 255;
};

#endif
