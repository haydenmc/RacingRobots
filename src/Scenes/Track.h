#pragma once

#include "Scene.h"
#include "Entities/Robot.h"
#include "Entities/Countdown.h"

#include <chrono>
#include <memory>
#include <set>
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
    const int START_COUNTDOWN_DURATION_MS = 3000;
    const int END_COUNTDOWN_DURATION_MS = 30000;
    const int BORDER_BUFFER = 32;
    const int FINISH_BUFFER = 64;
    const int FINISH_LINE_THICKNESS = 2;
    const std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> FINISH_LINE_COLOR = 
        {255, 255, 255, 255};

    // References
    std::vector<std::shared_ptr<Robot>> lineup;
    std::unique_ptr<Countdown> startCountdown;
    std::unique_ptr<Countdown> endCountdown;

    // Race state
    bool raceStarted = false;
    bool endCountdownStarted = false;
    std::set<std::shared_ptr<Robot>> finishedRobots;
    std::vector<std::shared_ptr<Robot>> orderedFinisherListDesc;

    // Track methods
    void StartRace();
    void EndRace();
    bool HasRobotFinished(const std::shared_ptr<Robot> robot);
};