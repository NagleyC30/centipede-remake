#ifndef		__HPP_BUTTON__
#define		__HPP_BUTTON__

#include "game_objects.hpp"
#include "constants.hpp"
#include <SDL3/SDL.h>
#include <functional>

// A clickable button drawn with SDL primitives. Activated by a left click
// (press and release inside it), or by pressing Space or Enter.
class Button : public GameObject {
   public:
	   Button(const char* label, float x = BUTTON_X, float y = BUTTON_Y, float w = BUTTON_WIDTH, float h = BUTTON_HEIGHT);
	   void setCallback(std::function<void()> callback);
	   void update(float deltaTime) override;
   private:
	   std::function<void()> onActivate;
	   const char* label;
	   SDL_FRect rect;
	   bool wasMouseDown = false;
	   // True while a click that started on the button is still held
	   bool armed = false;
};


#endif
