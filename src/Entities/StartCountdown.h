#pragma once

#include "..\IGameEntity.h"
#include "..\Text.h"
#include "..\Utilities\Event.h"
#include "SDL.h"

/**
 * @brief The StartCountdown displays a simple 3, 2, 1, countdown sequence
 *        and then signals when it is finished.
 */
class StartCountdown : IGameEntity
{
public:
    /* Events */
    Event<> Completed;

    /* Constructor/Destructor */
    StartCountdown(SDL_Renderer* renderer, unsigned int totalSeconds);

    /* Public methods */
    void Start();
    double GetX();
    double GetY();
    void SetX(double x);
    void SetY(double y);

    /* IGameEntity */
    void Draw() override;
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    SDL_Renderer* renderer;
    bool running = false;
    unsigned int totalSeconds = 0;
    unsigned int currentSecond = 0;
    std::unique_ptr<Text> text;
    std::chrono::milliseconds elapsedTimeMs;
    double x = 0.0;
    double y = 0.0;
};