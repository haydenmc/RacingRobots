#pragma once

#include "IGameEntity.h"
#include "Entities/Robot.h"
#include "Scene.h"

#include <chrono>
#include <map>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Scene; // forward declare since these are circular dependencies

enum class SceneId
{
    Title,
    Track
};

class Game : 
    public std::enable_shared_from_this<Game>
{
public:
    Game(int w, int h, int frameRateLimit = 0);
    void Start();
    void ChangeScene(SceneId toScene);

    /* Getters/Setters */
    SDL_Renderer* GetSDLRenderer();

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
