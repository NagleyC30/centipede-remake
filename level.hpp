#ifndef     __HPP_LEVEL__
#define     __HPP_LEVEL__


class Level {
    public:
        void load(int levelNumber);
        void reset();
        void update(float dt);
        void render(SDL_Renderer* renderer);

    private:
        void spawnPlayer();
        void spawnCentipede();
        void spawnMushrooms();
};

#endif
