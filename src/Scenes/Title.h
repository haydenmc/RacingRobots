#pragma once

#include "Scene.h"
#include "SDL.h"

class Title : public Scene
{
public:
    Title(SDL_Renderer* sdlRenderer);

private:
    SDL_Renderer* sdlRenderer;
};