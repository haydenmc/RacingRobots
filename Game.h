#pragma once

#include "Graphic.h"

#include <chrono>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
    Game(int w, int h, int frameRateLimit = 0);
    void Start();

private:
    // Private methods
    void initialize();
    void draw();
    void close();

    // SDL members
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlWindowRenderer = nullptr;

    // Graphics
    std::unique_ptr<Graphic> logoGraphic;

    // Misc members
    bool isInitialized = false;
    int windowWidth;
    int windowHeight;
    int frameRateLimit;
    std::chrono::duration<double, std::milli> timePerFrame;

    int logoX;
    int logoY;
};
