#include "mushroom.hpp"
#include "player.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "constants.hpp"
#include "centipede.hpp"
#include "text.hpp"
#include "button.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <random>


int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();
    if (!engine.isInitialized()) {
        return 1;
    }
    
    // Create all scenes
    Scene titleScreen;
    Scene game;
    Scene gameOver;

    // Scenes own their objects (unique_ptr), so everything is heap-allocated here.
    // Title screen: Space starts the game
    auto start = std::make_unique<Button>(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    start->setCallback([&engine, &game]() {
        engine.setScene(&game);
    });
    titleScreen.addObject(std::move(start));
    titleScreen.addObject(std::make_unique<Text>("assets/title.png"));

    /*
        (Re)build the game scene including
        - Mushrooms
        - Player
        - Centipede
    */
    // Seed once; resetGame reuses the generator for every new game.
    std::random_device rd;
    std::mt19937 gen(rd());
    auto resetGame = [&game, &gen]() {
        // Destroy the previous game's objects before building a fresh set
        game.clear();

        // Pick distinct cells so mushrooms never stack on top of each other
        std::vector<std::pair<int, int>> cells;
        for (int row = 1; row <= NUM_ROWS - 2; row++) {
            for (int col = 0; col < NUM_COLS; col++) {
                cells.emplace_back(col, row);
            }
        }
        std::shuffle(cells.begin(), cells.end(), gen);

        std::uniform_int_distribution<> countDist(40, 60);
        int mushroomCount = countDist(gen);
        for (int i = 0; i < mushroomCount; i++) {
            game.addObject(std::make_unique<Mushroom>(cells[i].first * CELL_SIZE, cells[i].second * CELL_SIZE));
        }

        // Player goes in the final visible row (NUM_ROWS - 1; NUM_ROWS * CELL_SIZE is off-screen), middle column
        game.addObject(std::make_unique<Player>(NUM_COLS / 2 * CELL_SIZE, (NUM_ROWS - 1) * CELL_SIZE));

        // Spawns the centipedes, and a faster wave each time they are all cleared
        game.addObject(std::make_unique<WaveSpawner>());
    };
    // Build the first game so it is ready when the title screen is dismissed
    resetGame();

    // Game over screen: Space restarts with a fresh game
    gameOver.addObject(std::make_unique<Text>("assets/gameOver.png"));
    auto restart = std::make_unique<Button>(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    // resetGame is copied in (its captures are all references to locals that outlive the engine loop)
    restart->setCallback([&engine, &game, resetGame]() {
        resetGame();
        engine.setScene(&game);
    });
    gameOver.addObject(std::move(restart));

    // Switch to the game over scene when the player dies
    Player::setOnDeathCallback([&engine, &gameOver]() {
        engine.setScene(&gameOver);
    });

    engine.setScene(&titleScreen);
    engine.run();
    engine.shutdown();

    return 0; 
}
