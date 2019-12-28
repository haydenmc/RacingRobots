#include "DvdLogo.h"

#include <algorithm>

DvdLogo::DvdLogo(
    SDL_Renderer* renderer,
    double minX,
    double minY,
    double maxX,
    double maxY,
    double velocityX,
    double velocityY,
    double scale
): 
    Graphic(renderer, "../assets/dvdlogo.png"),
    minX(minX),
    minY(minY),
    maxX(maxX),
    maxY(maxY),
    velocityX(velocityX),
    velocityY(velocityY),
    scale(scale)
{
    this->width = this->sourceWidth * this->scale;
    this->height = this->sourceHeight * this->scale;
}

void DvdLogo::Update(std::chrono::nanoseconds deltaTime)
{
    auto deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

    // Add velocity based on elapsed time
    this->x += this->velocityX * deltaTimeMs.count();
    this->y += this->velocityY * deltaTimeMs.count();
    
    // "bounce" off the edges of the rect
    if (this->x < this->minX || this->x > (this->maxX - this->width))
    {
        this->velocityX *= -1;
    }
    if (this->y < this->minY || this->y > (this->maxY - this->height))
    {
        this->velocityY *= -1;
    }

    // Clamp position to bounds
    this->x = std::clamp(this->x, this->minX, this->maxX - this->width);
    this->y = std::clamp(this->y, this->minY, this->maxY - this->height);
}