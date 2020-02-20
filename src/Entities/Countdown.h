#pragma once

#include "..\IGameEntity.h"
#include "..\Text.h"
#include "..\Utilities\Event.h"
#include "SDL.h"

/**
 * @brief The Countdown displays a simple second countdown sequence
 *        and then signals when it is finished.
 */
class Countdown : IGameEntity
{
public:
    /* Events */
    Event<> Completed;

    /* Constructor/Destructor */
    Countdown(SDL_Renderer* renderer,
        std::chrono::milliseconds durationMs,
        unsigned short numDigits = 2,
        unsigned short numDecimals = 0);

    /* Public methods */
    void Start();
    void Stop();
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
    std::chrono::milliseconds durationMs;
    unsigned short numDecimals;
    std::unique_ptr<Text> text;
    std::chrono::milliseconds elapsedTimeMs;
    std::chrono::milliseconds remainingTimeMs;
    double x = 0.0;
    double y = 0.0;
    std::wstring displayFormat;
};