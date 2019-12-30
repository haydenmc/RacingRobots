#include "Game.h"

#include <stdexcept>
#include <thread>
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

    std::chrono::high_resolution_clock::time_point lastFrameTime
        = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point lastUpdateTime
        = std::chrono::high_resolution_clock::now();
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
            std::chrono::high_resolution_clock::time_point now
                = std::chrono::high_resolution_clock::now();
            auto frameDelta = now - lastFrameTime;

            if (frameDelta < this->timePerFrame)
            {
                auto sleepTime = this->timePerFrame - frameDelta;
                std::this_thread::sleep_for(sleepTime);
            }
        }

        // Update
        auto currentUpdateTime = std::chrono::high_resolution_clock::now();
        auto updateDelta = currentUpdateTime - lastUpdateTime;
        this->update(updateDelta);
        lastUpdateTime = currentUpdateTime;

        // Draw
        this->draw();

        // Update last frame time
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
}
#pragma endregion

#pragma region Private Methods
void Game::initialize()
{
    // Do some math
    if (this->frameRateLimit != 0)
    {
        this->timePerFrame = std::chrono::nanoseconds( std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / static_cast<long long>(this->frameRateLimit));
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

    // Set some things
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Create renderer for window
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    if (this->frameRateLimit == 0)
    {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }
    this->sdlWindowRenderer = SDL_CreateRenderer(this->sdlWindow, -1, rendererFlags);
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

    this->isInitialized = true;
}

void Game::update(std::chrono::nanoseconds deltaTime)
{
    // Update all entities
    for (auto& entity : this->gameEntities)
    {
        entity->Update(deltaTime);
    }
}

void Game::draw()
{
    //Clear screen
    SDL_RenderClear(this->sdlWindowRenderer);

    //Render entities
    for (auto& entity : this->gameEntities)
    {
        entity->Draw();
    }

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