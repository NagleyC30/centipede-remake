#include "mushroom.hpp"
#include "player.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "centipede.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <random>


int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();
    Scene scene;

    // Create the grid (invisible) that we will use to place the mushrooms and player
    

    // Create a vector of mushrooms
    std::vector<Mushroom> mushrooms;
    
    // Create a random device
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> countDist(40, 60);
    std::uniform_int_distribution<> colDist(0, NUM_COLS - 1);
    std::uniform_int_distribution<> rowDist(1, NUM_ROWS - 3);

    int mushroomCount = countDist(gen);

    for (int i = 0; i < mushroomCount; i++) {
        int col = colDist(gen);
        int row = rowDist(gen);

        int x = col * CELL_SIZE;
        int y = row * CELL_SIZE;

        mushrooms.emplace_back(x, y);
    }

    for (auto& m : mushrooms) {
        scene.addObject(&m);
    }

    // Generate the player and add it to the scene (final row, middle column)
    Player player(NUM_COLS / 2 * CELL_SIZE, (NUM_ROWS - 1) * CELL_SIZE);
    scene.addObject(&player);

    // Add centipede to scene
    std::vector<Centipede*> centipedes;
    for (size_t i=0; i<12; i++) {
        centipedes.emplace_back(new Centipede(NUM_COLS / 2 * CELL_SIZE - i * CELL_SIZE, 0));
        scene.addObject(centipedes[i]);
    }
    
    engine.setScene(&scene);
    engine.run();

    return 0; 
}
