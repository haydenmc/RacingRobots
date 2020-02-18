#pragma once

#include "Scene.h"
#include "Entities/Robot.h"
#include "Entities/StatCard.h"
#include "Text.h"

#include <chrono>
#include <memory>
#include <vector>

/**
 * @brief Represents the lobby where the robots prep for the race.
 */
class Lobby : public Scene
{
public:
    /* Constructor/Destructor */
    Lobby(
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
    std::shared_ptr<Text> headerText;
    std::shared_ptr<Text> timerText;
    std::vector<std::shared_ptr<Robot>> robotLineup;
    std::vector<std::shared_ptr<StatCard>> statCards;

    // Lobby state
    std::chrono::milliseconds elapsedTimeMs;
    std::chrono::milliseconds lastTimerUpdateMs;
};