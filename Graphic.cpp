#include "Graphic.h"

#include <stdexcept>

Graphic::Graphic(SDL_Renderer* renderer, std::string imagePath) : 
    renderer(renderer)
{
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if(loadedSurface == nullptr)
    {
        std::string errorString = "Unable to load image! IMG_Error: " + std::string(IMG_GetError());
        throw std::runtime_error(errorString);
    }
    this->sourceWidth = loadedSurface->w;
    this->sourceHeight = loadedSurface->h;
    this->width = this->sourceWidth;
    this->height = this->sourceHeight;

    // Create texture from surface pixels
    this->texture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
    if(this->texture == nullptr)
    {
        std::string errorString = "Unable to create texture from image! SDL Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
}

Graphic::~Graphic()
{
    SDL_DestroyTexture(this->texture);
}

void Graphic::Draw()
{
    SDL_Rect targetRect{
        static_cast<int>(this->x),      // X
        static_cast<int>(this->y),      // Y
        static_cast<int>(this->width),  // W
        static_cast<int>(this->height)  // H
    };
    SDL_RenderCopyEx(
        this->renderer,
        this->texture,
        nullptr,
        &targetRect,
        0,
        nullptr,
        SDL_RendererFlip::SDL_FLIP_NONE
    );
}

void Graphic::Update(std::chrono::nanoseconds deltaTime)
{ }

void Graphic::SetX(double x)
{
    this->x = x;
}

void Graphic::SetY(double y)
{
    this->y = y;
}