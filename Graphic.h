#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Graphic
{
public:
    Graphic(SDL_Renderer* renderer, std::string imagePath);
    ~Graphic();
    void Draw();
    void Update();
    void SetVelocityX(double velocityX);
    void SetVelocityY(double velocityY);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    double x;
    double y;
    double w;
    double h;
    double velocityX;
    double velocityY;
};
