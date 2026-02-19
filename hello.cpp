#include "car.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();
    

    /* Here we are going to initialize all of the objects we want in the main scene.
     * Then, have engine run the scene. No advanced start page or anything yet */
    Scene scene;
    
    /* We need to call a method that sets up the level. This means setting up the 
     * mushrooms in a random way. Seperate the screen into a small "board" where
     * each space is the size of the rectangles we are using for each sprite. */
    // Mushroom mushroom;
    
    Car car;
    
    // Adds objects to the scene varaible
    scene.addObject(&car);

    // Engine sets the scene to whatever scene varaible we want
    engine.setScene(&scene);

    // Engine runs that scene
    engine.run();

    return 0;
}

