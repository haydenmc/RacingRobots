#pragma once

#include "..\IGameEntity.h"
#include "Robot.h"
#include "SDL.h"
#include "Text.h"

#include <memory>
#include <tuple>

/**
 * @brief The StatCard is a card that displays stats and information
 *        about a particular robot.
 */
class StatCard : IGameEntity
{
public:
    StatCard(
        SDL_Renderer* renderer,
        std::weak_ptr<Robot> robot
    );

    double GetX();
    double GetY();
    void SetX(double x);
    void SetY(double y);
    double GetWidth();
    double GetHeight();
    void SetWidth(double width);
    void SetHeight(double height);

    /* IGameEntity */
    void Draw() override;
    void Update(std::chrono::nanoseconds deltaTime);

private:
    /* Renderer, robot constructor values */
    SDL_Renderer* sdlRenderer;
    std::weak_ptr<Robot> weakRobot;

    /* Text entities */
    std::unique_ptr<Text> nameText;

    const double cornerLength = 32.0;
    const double borderWidth = 2.0;
    const std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> borderColor = 
        {255, 255, 255, 255};
    double x = 0.0;
    double y = 0.0;
    double width = 150.0;
    double height = 400.0;
};