#pragma once

// Define the number of rows and columns for the invisible grid
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CELL_SIZE 32

// Define values for the title
#define TITLE_WIDTH (0.75f * WINDOW_WIDTH)
#define TITLE_HEIGHT (0.5f * WINDOW_HEIGHT)
#define TITLE_X (WINDOW_WIDTH - TITLE_WIDTH)/2
#define TITLE_Y (0.13f * WINDOW_HEIGHT)

// Define values for the start / play again button
#define BUTTON_WIDTH 260.0f
#define BUTTON_HEIGHT 60.0f
#define BUTTON_X ((WINDOW_WIDTH - BUTTON_WIDTH) / 2)
#define BUTTON_Y 438.0f

// Title screen layout: logo on top, rules card in the middle, button below
#define MENU_LOGO_WIDTH 400.0f
#define MENU_LOGO_HEIGHT 200.0f
#define MENU_LOGO_X ((WINDOW_WIDTH - MENU_LOGO_WIDTH) / 2)
#define MENU_LOGO_Y 10.0f
#define RULES_X 100.0f
#define RULES_Y 218.0f
#define RULES_WIDTH 600.0f
#define RULES_HEIGHT 205.0f

// Define grid
#define NUM_ROWS (WINDOW_HEIGHT / CELL_SIZE)
#define NUM_COLS (WINDOW_WIDTH / CELL_SIZE)
