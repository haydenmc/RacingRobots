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
    Lobby,
    Track
};

class Game : 
    public std::enable_shared_from_this<Game>
{
public:
    /* Statics/Constants */
    static const int LobbyTimeSeconds = 5;

    /* Constructor */
    Game(int w, int h, int frameRateLimit = 0);

    /* Public methods */
    void Start();
    void ChangeScene(SceneId toScene);

    /* Getters/Setters */
    void SetRacerCount(unsigned int count);
    unsigned int GetRacerCount();
    SDL_Renderer* GetSDLRenderer();
    const std::vector<std::shared_ptr<Robot>>& GetRobotLineup();

    /* Robot roster management */
    void GenerateNewLineup();

private:
    // Const values
    unsigned int racerCount = 5;

    // SDL members
    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlWindowRenderer = nullptr;

    // Game data
    std::map<SceneId, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;
    std::vector<std::shared_ptr<Robot>> robotRoster;
    std::vector<std::shared_ptr<Robot>> robotLineup;

    // Misc members
    bool isInitialized = false;
    int windowWidth = 0;
    int windowHeight = 0;
    int frameRateLimit = 0;
    std::chrono::nanoseconds timePerFrame;

    // Private methods
    void initialize();
    void initializeScenes();
    void loadRobots();
    void update(std::chrono::nanoseconds deltaTime);
    void draw();
    void close();
};
