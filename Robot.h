#pragma once

#include "Graphic.h"

class Robot : public Graphic
{
public:
    Robot(
        SDL_Renderer* renderer,
        std::wstring name,
        std::string imagePath
    );
private:
    std::wstring name;
    unsigned int totalWins = 0;
    unsigned int totalRaces = 0;
};