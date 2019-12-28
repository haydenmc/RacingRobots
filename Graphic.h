#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <chrono>
#include <string>

class Graphic
{
public:
    Graphic(SDL_Renderer* renderer, std::string imagePath);
    ~Graphic();
    void Draw();
    virtual void Update(std::chrono::nanoseconds deltaTime);
    void SetX(double x);
    void SetY(double y);

protected:
    double x;
    double y;
    double sourceWidth;
    double sourceHeight;
    double width;
    double height;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};
