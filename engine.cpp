#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Want to share these.  Easiest (and quick) way
// is with a static data structure.
std::vector<SDL_Event> Engine::keyEvents;

Engine::Engine() { init(); }

SDL_Renderer* Engine::getRenderer() { return this->renderer; };

void Engine::setScene(Scene *scene) { this->scene = scene; }
void Engine::run() {
	running = true;
	// Track real frame times so movement is independent of how long a frame takes.
	Uint64 lastFrame = SDL_GetTicksNS();
	while (running) {
		Uint64 frameStart = SDL_GetTicksNS();
		float deltaTime = (frameStart - lastFrame) / 1000000.0f;
		lastFrame = frameStart;
		// Clamp after a stall (e.g. window drag) so objects don't jump through each other.
		if (deltaTime > MAX_FRAME_MS) deltaTime = MAX_FRAME_MS;

		// Clear the events from the last frame first.
		Engine::keyEvents.clear();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				SDL_Log("Shutting down...");
				running = false;
			}
			// Ignore OS key-repeat: held keys are polled with SDL_GetKeyboardState instead,
			// and repeats would let a held Space skip past the title/game over screens.
			if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
				// Esc quits from any scene
				if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
					running = false;
				}
				// Since we are storing copies of events, this
				// works.  Would not work if we were storing pointers
				// as event is a local variable to this function and
				// would always have the same address.
				Engine::keyEvents.push_back(event);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		scene->updateScene(deltaTime);
		SDL_RenderPresent(renderer);
		// Sleep only for whatever is left of this frame's time budget.
		Uint64 elapsed = SDL_GetTicksNS() - frameStart;
		if (elapsed < targetFrameTimeNS) {
			SDL_DelayNS(targetFrameTimeNS - elapsed);
		}
	}
}

bool Engine::init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	// Gotta draw somewhere....
	window = SDL_CreateWindow("Return of the Centipede", 800, 600, 0);

	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// Who is in charge of drawing?
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	SDL_SetRenderVSync(renderer, 0);

	return true;
}

void Engine::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}