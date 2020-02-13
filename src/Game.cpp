#include "Game.h"

#include "SDL_ttf.h"
#include "Scenes/Title.h"
#include "Scenes/Lobby.h"
#include "Scenes/Track.h"
#include "Text.h"

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
            // TODO: Use media timers to make this more accurate
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

void Game::ChangeScene(SceneId toScene)
{
    if (this->currentScene)
    {
        this->currentScene->Hidden(); // Hide existing scene
    }
    this->currentScene = this->scenes[toScene];
    this->currentScene->Showing();
}

void Game::SetRacerCount(unsigned int count)
{
    this->racerCount = count;
}

unsigned int Game::GetRacerCount()
{
    return this->racerCount;
}

SDL_Renderer* Game::GetSDLRenderer()
{
    return this->sdlWindowRenderer;
}

const std::vector<std::shared_ptr<Robot>>& Game::GetRobotLineup()
{
    return this->robotLineup;
}

void Game::GenerateNewLineup()
{
    // Shuffle the lineup, then take the first up to racerCount
    auto shuffledRoster = this->robotRoster;
    std::shuffle(
        shuffledRoster.begin(),
        shuffledRoster.end(),
        std::default_random_engine()
    );
    this->robotLineup.clear();
    if (shuffledRoster.size() < this->racerCount)
    {
        std::cerr << "Not enough robots in the roster "
                     "to fill the starting lineup. :(" << std::endl;
    }
    unsigned int lineupCount = std::min(
        static_cast<unsigned int>(shuffledRoster.size()),
        this->racerCount
    );
    for (unsigned int i = 0; i < lineupCount; ++i)
    {
        this->robotLineup.push_back(shuffledRoster.at(i));
    }
}
#pragma endregion

#pragma region Private Methods
void Game::initialize()
{
    // Do some math
    if (this->frameRateLimit != 0)
    {
        this->timePerFrame = std::chrono::nanoseconds(
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)) / 
            static_cast<long long>(this->frameRateLimit)
        );
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string errorString = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }
    
    // Create window
    this->sdlWindow = SDL_CreateWindow(
        "Racing Robots!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );
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

    // Initialize text
    Text::Initialize();

    // Load ze robots!
    this->loadRobots();

    // Init scenes
    this->initializeScenes();

    // Start us off on the title scene
    this->ChangeScene(SceneId::Title);

    this->isInitialized = true;
}

void Game::initializeScenes()
{
    // Title scene
    this->scenes.insert_or_assign(SceneId::Title, std::make_shared<Title>
    (
        this->weak_from_this(),
        SDL_Rect{0, 0, windowWidth, windowHeight}
    ));

    // Lobby scene
    this->scenes.insert_or_assign(SceneId::Lobby, std::make_shared<Lobby>
    (
        this->weak_from_this(),
        SDL_Rect{0, 0, windowWidth, windowHeight}
    ));

    // Track scene
    this->scenes.insert_or_assign(SceneId::Track, std::make_shared<Track>
    (
        this->weak_from_this(),
        SDL_Rect{0, 0, windowWidth, windowHeight},
        this->robotRoster
    ));
}

void Game::loadRobots()
{
    auto defaultTraits = RobotTraits {
        std::tuple<double, double>(0.01, 0.02),        // minVelocityWindow
        std::tuple<double, double>(0.05, 0.20),        // maxVelocityWindow
        std::tuple<double, double>(0.000005, 0.0008),  // accelerationWindow
        std::tuple<double, double>(30.00, 60.00),      // maxStaminaWindow
        std::tuple<double, double>(0.10, 0.30)         // staminaRechargeRateWindow
    };

    // TODO: Load these from some kind of definition file
    // Square boy!
    this->robotRoster.push_back(
        std::make_shared<Robot>(
            this->sdlWindowRenderer,
            L"Square Boy",
            "assets/robot_01.png",
            defaultTraits
        )
    );
    // Blue Roundy
    this->robotRoster.push_back(
        std::make_shared<Robot>(
            this->sdlWindowRenderer,
            L"Blue Roundy",
            "assets/robot_02.png",
            defaultTraits
        )
    );
    // Spiky Lady
    this->robotRoster.push_back(
        std::make_shared<Robot>(
            this->sdlWindowRenderer,
            L"Spiky Lady",
            "assets/robot_03.png",
            defaultTraits
        )
    );
    // Pointy Orange
    this->robotRoster.push_back(
        std::make_shared<Robot>(
            this->sdlWindowRenderer,
            L"Pointy Orange",
            "assets/robot_04.png",
            defaultTraits
        )
    );
    // Boring Diamond
    this->robotRoster.push_back(
        std::make_shared<Robot>(
            this->sdlWindowRenderer,
            L"Boring Diamond",
            "assets/robot_05.png",
            defaultTraits
        )
    );
}

void Game::update(std::chrono::nanoseconds deltaTime)
{
    // Update current scene
    if (this->currentScene)
    {
        this->currentScene->Update(deltaTime);
    }
}

void Game::draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(this->sdlWindowRenderer, 0, 0, 0, 255);
    SDL_RenderClear(this->sdlWindowRenderer);

    // Draw current scene
    if (this->currentScene)
    {
        this->currentScene->Draw();
    }

    // Update screen
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