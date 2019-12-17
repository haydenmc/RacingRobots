#include "Game.h"
#include <exception>
#include <iostream>
#include <string>

Game::Game(int w, int h) :
    windowWidth(w),
    windowHeight(h)
{ }

void Game::Start()
{
    this->initialize();
    
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

        // Draw
        this->draw();
    }
}

void Game::initialize()
{
    //Initialize SDL
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
    SDL_Surface* logoSurface = IMG_Load("../assets/dvdlogo.png");
    if (logoSurface == nullptr)
    {
        std::string errorString = "Unable to load image! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }

    //Create texture from surface pixels
    this->logoTexture = SDL_CreateTextureFromSurface(this->sdlWindowRenderer, logoSurface);
    if(this->logoTexture == nullptr)
    {
        std::string errorString = "Unable to create texture from image! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(logoSurface);

    this->isInitialized = true;
}

void Game::draw()
{
    //Clear screen
    SDL_RenderClear(this->sdlWindowRenderer);

    //Render texture to screen
    SDL_RenderCopy(this->sdlWindowRenderer, this->logoTexture, nullptr, nullptr);

    //Update screen
    SDL_RenderPresent(this->sdlWindowRenderer);
}

void Game::close()
{
    // Deallocate logo surface
    SDL_DestroyTexture(this->logoTexture);
    this->logoTexture = nullptr;

    // Destroy window
    SDL_DestroyRenderer(this->sdlWindowRenderer);
    SDL_DestroyWindow(this->sdlWindow);
    this->sdlWindow = nullptr;
    this->sdlWindowRenderer = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}