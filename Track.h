#pragma once

#include "IGameEntity.h"
#include "Robot.h"

#include <vector>

class Track : public IGameEntity
{
public:
    Track(
        SDL_Renderer* renderer,
        SDL_Rect renderingBounds
    );

private:
    SDL_Renderer* renderer;
    SDL_Rect renderingBounds;
    std::vector<Robot> robots;
};