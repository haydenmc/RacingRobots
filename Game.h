#pragma once

#include "IGameEntity.h"

#include <chrono>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Game
{
public:
    Game(int w, int h, int frameRateLimit = 0);
    void Start();

private:
    // Private methods
    void initialize();
    void update(std::chrono::nanoseconds deltaTime);
    void draw();
    void close();

    // SDL members
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlWindowRenderer = nullptr;

    // Graphics
    std::vector<std::unique_ptr<IGameEntity>> gameEntities;

    // Misc members
    bool isInitialized = false;
    int windowWidth;
    int windowHeight;
    int frameRateLimit;
    std::chrono::nanoseconds timePerFrame;

    int logoX;
    int logoY;
};
