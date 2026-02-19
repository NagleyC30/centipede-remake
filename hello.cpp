#include "car.hpp"
#include "engine.hpp"
#include "game_objects.hpp"

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene scene;
    Car car;
    
    // Adds objects to the scene varaible
    scene.addObject(&car);

    // Engine sets the scene to whatever scene varaible we want
    engine.setScene(&scene);

    // Engine runs that scene
    engine.run();
}

