# Return of the Centipede

A Centipede remake built with SDL3, SDL3_image and glm.

## Build

Place SDL and SDL_image sources in `vendored/SDL` and `vendored/SDL_image`, then:

    cmake -B build
    cmake --build build

The `assets/` folder is copied next to the executable on every build, so the game can be launched from any directory.

## Controls

| Key | Action |
| --- | --- |
| Space | Start / restart (title and game over screens) |
| A / Left arrow | Move left |
| D / Right arrow | Move right |
| J / Space | Shoot |
| Esc | Quit |

Clearing a wave of centipedes starts a new, faster one. Mushrooms darken as they take damage.
