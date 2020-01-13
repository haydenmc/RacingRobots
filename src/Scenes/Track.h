#pragma once

#include "Scene.h"
#include "Entities/Robot.h"

#include <chrono>
#include <memory>
#include <vector>

/**
 * @brief Represents the racing track and contains
 *        all of the robots participating in the race.
 */
class Track : public Scene
{
public:
    // Constructor/Destructor
    Track(
        SDL_Renderer* renderer,
        SDL_Rect renderingBounds,
        std::vector<std::shared_ptr<Robot>> robots
    );

    // Track methods
    void StartRace();

private:
    // Constants
    const int BORDER_BUFFER = 32;

    // References
    SDL_Renderer* renderer;
    SDL_Rect renderingBounds;
    std::vector<std::shared_ptr<Robot>> robots;

    // Track state
    bool raceStarted;
};