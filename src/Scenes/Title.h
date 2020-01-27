#pragma once

#include "Game.h"
#include "Scene.h"
#include "SDL.h"
#include "Text.h"
#include "Utilities/Tween.h"

class Title : public Scene
{
public:
    Title(
        std::weak_ptr<Game> game,
        SDL_Rect sceneBounds
    );

    /* Scene */
    void Showing() override;
    void Hidden() override;
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    std::shared_ptr<Text> titleText = nullptr;
    std::shared_ptr<Tweener<double>> titleTextAnimation = nullptr;
};