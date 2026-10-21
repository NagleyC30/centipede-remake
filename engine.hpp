#ifndef			__HPP_ENGINE__
#define			__HPP_ENGINE__

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include "game_objects.hpp"

#define FPS 60
#define MAX_EVENTS 128
// Target frame time in nanoseconds.
#define targetFrameTimeNS (1000000000ULL / FPS)
// Longest frame we will simulate, in ms (avoids huge jumps after a stall).
#define MAX_FRAME_MS 33.0f

class Scene;

// Singleton pattern to ensure we only have one
// instance of Engine at a time.
class Engine {
	public:
		// Returns the instance.
		static Engine& instance(){
			static Engine instance;
			return instance;
		}

		// Delete copy operators.  No copies!
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		SDL_Renderer* getRenderer();
		void setScene(Scene* scene);
		void run();

		Engine();
		~Engine() = default;

		bool init();
		bool isInitialized() const { return initialized; }

		// Returns the texture for an asset path (relative to the executable),
		// loading it on first use. Textures are shared and owned by the engine.
		SDL_Texture* getTexture(const char* path);

		void shutdown();

		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		bool initialized = false;
		bool running = false;
		// Texture cache, keyed by asset path
		std::unordered_map<std::string, SDL_Texture*> textures;
		// Notice that we are storing copies of the
		// events, not pointers or references.
		static std::vector<SDL_Event> keyEvents;
		Scene* scene = nullptr;

};

#endif