#pragma once

#include "Scene.h"
#include "Entities/Robot.h"
#include "Entities/StartCountdown.h"

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
        std::weak_ptr<Game> game,
        SDL_Rect renderingBounds
    );

    /* Scene */
    void Showing() override;
    void Hidden() override;
    void Draw() override;
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    // Constants
    const int BORDER_BUFFER = 32;

    // References
    std::vector<std::shared_ptr<Robot>> lineup;
    std::unique_ptr<StartCountdown> countdown;

    // Track state
    bool raceStarted;

    // Track methods
    void StartRace();
};