#include "Game.h"
#include <stdexcept>
#include <iostream>
#include <string>

#pragma region Public Methods
Game::Game(int w, int h, int frameRateLimit): 
    windowWidth(w),
    windowHeight(h),
    frameRateLimit(frameRateLimit)
{ }

void Game::Start()
{
    this->initialize();
    
    int lastFrameTime = SDL_GetTicks();
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        // Handle events first
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        
        // Cap frame rate (if specified)
        if (this->frameRateLimit != 0)
        {
            if ((SDL_GetTicks() - lastFrameTime) <= this->timePerFrameMs)
            {
                SDL_Delay(this->timePerFrameMs - (SDL_GetTicks() - lastFrameTime));
            }
        }

        // Draw
        this->draw();

        lastFrameTime = SDL_GetTicks();
    }
}
#pragma endregion

#pragma region Private Methods
void Game::initialize()
{
    // Do some math
    if (this->frameRateLimit != 0)
    {
        this->timePerFrameMs = 1000 / static_cast<double>(this->frameRateLimit);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string errorString = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }
    
    // Create window
    this->sdlWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (this->sdlWindow == nullptr)
    {
        std::string errorString = "Window could not be created! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }

    // Create renderer for window
    this->sdlWindowRenderer = SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (this->sdlWindowRenderer == nullptr)
    {
        std::string errorString = "Unable to create window renderer! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(this->sdlWindowRenderer, 0x00, 0x00, 0x00, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::string errorString = "Unable to initialize SDL_image! IMG_Error: " + std::string(IMG_GetError());
        throw std::runtime_error(errorString);
    }

    // Load logo
    this->logoGraphic = std::make_unique<Graphic>(this->sdlWindowRenderer, "../assets/dvdlogo.png");

    this->isInitialized = true;
}

void Game::draw()
{
    //Clear screen
    SDL_RenderClear(this->sdlWindowRenderer);

    //Render texture to screen
    this->logoGraphic->Draw();

    //Update screen
    SDL_RenderPresent(this->sdlWindowRenderer);
}

void Game::close()
{
    // Destroy window
    SDL_DestroyRenderer(this->sdlWindowRenderer);
    SDL_DestroyWindow(this->sdlWindow);
    this->sdlWindow = nullptr;
    this->sdlWindowRenderer = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
#pragma endregion