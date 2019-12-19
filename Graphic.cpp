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
    this->w = loadedSurface->w;
    this->h = loadedSurface->h;

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
        static_cast<int>(this->x), // X
        static_cast<int>(this->y), // Y
        static_cast<int>(this->w), // W
        static_cast<int>(this->h)  // H
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

void Graphic::Update()
{
    this->x += this->velocityX;
    this->y += this->velocityY;
}

void Graphic::SetVelocityX(double velocityX)
{
    this->velocityX = velocityX;
}

void Graphic::SetVelocityY(double velocityY)
{
    this->velocityY = velocityY;
}