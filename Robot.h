#pragma once

#include "Graphic.h"

class Robot : Graphic
{
public:
    Robot(
        SDL_Renderer* renderer,
        std::string name,
        std::string imagePath
    );
private:
    std::string name;
    unsigned int totalWins = 0;
    unsigned int totalRaces = 0;
};