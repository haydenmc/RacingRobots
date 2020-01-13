#pragma once

#include "IGameEntity.h"
#include "Entities/Robot.h"
#include "Scenes/Track.h"

#include <chrono>
#include <map>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

enum class SceneId
{
    Title,
    Track
};

class Game
{
public:
    Game(int w, int h, int frameRateLimit = 0);
    void Start();

private: 
    // Private methods
    void initialize();
    void initializeScenes();
    void loadRobots();
    void update(std::chrono::nanoseconds deltaTime);
    void draw();
    void close();

    // SDL members
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlWindowRenderer = nullptr;

    // Game data
    std::map<SceneId, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;
    std::vector<std::shared_ptr<Robot>> robotRoster;

    // Misc members
    bool isInitialized = false;
    int windowWidth = 0;
    int windowHeight = 0;
    int frameRateLimit = 0;
    std::chrono::nanoseconds timePerFrame;
};
