#pragma once

#include "Scene.h"
#include "SDL.h"
#include "Text.h"
#include "Utilities/Tween.h"

class Title : public Scene
{
public:
    Title(
        SDL_Renderer* sdlRenderer,
        SDL_Rect sceneBounds
    );

    /* Scene */
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    std::shared_ptr<Text> titleText = nullptr;
    std::shared_ptr<Tweener<double>> titleTextAnimation = nullptr;
};