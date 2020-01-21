#include "Title.h"

#pragma region Constructor/Destructor
Title::Title(
    SDL_Renderer* sdlRenderer,
    SDL_Rect sceneBounds
) : 
    Scene(sdlRenderer, sceneBounds)
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
    // Center text in scene
    auto titleTextWidth = this->titleText->GetWidth();
    auto titleTextHeight = this->titleText->GetHeight();
    this->titleText->SetX(
        (this->sceneBounds.w / 2.0) - 
        (titleTextWidth / 2.0) + 
        this->sceneBounds.x
    );
    this->titleText->SetY(
        (this->sceneBounds.h / 2.0) - 
        (titleTextHeight / 2.0) + 
        this->sceneBounds.x
    );
    this->gameEntities.push_back(this->titleText);
}
#pragma endregion

#pragma region Scene
void Title::Update(std::chrono::nanoseconds deltaTime)
{
    Scene::Update(deltaTime);
    // And also update our animation!
    //this->titleTextAnimation->Update(deltaTime);
}
#pragma endregion