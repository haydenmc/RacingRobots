#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
    Game(int w, int h);
    void Start();

private:
    // Private methods
    void initialize();
    void draw();
    void close();

    // SDL members
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlWindowRenderer = nullptr;
    SDL_Texture* logoTexture = nullptr;

    // Misc members
    bool isInitialized = false;
    int windowWidth;
    int windowHeight;
};
