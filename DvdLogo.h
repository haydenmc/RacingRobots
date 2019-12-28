#pragma once

#include "Graphic.h"

class DvdLogo : public Graphic
{
public:
    DvdLogo(
        SDL_Renderer* renderer,
        double minX,
        double minY,
        double maxX,
        double maxY,
        double velocityX = 0.1,
        double velocityY = 0.1,
        double scale     = 0.5
    );
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    double minX;
    double minY;
    double maxX;
    double maxY;
    double velocityX;
    double velocityY;
    double scale;
};