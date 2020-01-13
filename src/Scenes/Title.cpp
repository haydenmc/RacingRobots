#include "Title.h"

#include "Utilities/Tween.h"

#pragma region Constructor/Destructor
Title::Title(SDL_Renderer* sdlRenderer) : 
    sdlRenderer(sdlRenderer)
{
    // Instantitate scene elements
    this->titleText = std::make_shared<Text>
    (
        this->sdlRenderer,
        FontFace::Default,
        64,
        SDL_Color{255, 255, 255, 255},
        "Racing Robots!"
    );
    this->gameEntities.push_back(this->titleText);

    // Set up tweening for title text animation
    this->titleTextAnimation = std::make_shared<Tweener<QuartOutEasingFunction, double>>
    (
        std::bind(&Text::SetX, this->titleText, std::placeholders::_1),
        100.0,
        500.0,
        std::chrono::milliseconds(2000)
    );

    // Start the animation!
    this->titleTextAnimation->Start();
}
#pragma endregion

#pragma region Scene
void Title::Update(std::chrono::nanoseconds deltaTime)
{
    Scene::Update(deltaTime);
    // And also update our animation!
    this->titleTextAnimation->Update(deltaTime);
}
#pragma endregion