#include "Title.h"

#pragma region Constructor/Destructor
Title::Title(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    Scene(game, sceneBounds)
{
    // Instantitate scene elements
    this->titleText = std::make_shared<Text>
    (
        this->sdlRenderer,
        FontFace::Default,
        64,
        SDL_Color{255, 255, 255, 255},
        L"Racing Robots!"
    );

    // Set text out-of-bounds to animate in
    auto titleTextWidth = this->titleText->GetWidth();
    auto titleTextHeight = this->titleText->GetHeight();
    double startX = this->sceneBounds.x - titleTextWidth;
    double inX = this->sceneBounds.x + 48.0;
    double deltaInX = inX - startX;
    double outX = this->sceneBounds.w;
    double deltaOutX = outX - inX;
    this->titleText->SetX(
        startX
    );
    this->titleText->SetY(
        (this->sceneBounds.h / 2.0) - 
        (titleTextHeight / 2.0) + 
        this->sceneBounds.y
    );
    this->gameEntities.push_back(this->titleText);

    // Set up title text animation
    this->titleTextEntranceAnimation = std::make_shared<Tweener<double>>(
        &EasingFunctions::QuartOutEase<double>,
        [this, startX, deltaInX](double value)
        {
            // Bring into view, left-aligned
            auto newX = startX + (deltaInX * value);
            this->titleText->SetX(newX);
        },
        0.0,
        1.0,
        std::chrono::milliseconds(1200)
    );

    this->titleTextExitAnimation = std::make_shared<Tweener<double>>(
        &EasingFunctions::QuartInEase<double>,
        [this, inX, deltaOutX](double value)
        {
            // Bring out of view, left-aligned
            auto newX = inX + (deltaOutX * value);
            this->titleText->SetX(newX);
        },
        0.0,
        1.0,
        std::chrono::milliseconds(1200)
    );

    this->titleTextEntranceAnimation->Completed.Subscribe([this](){
        this->titleTextExitAnimation->Start();
    });

    this->titleTextExitAnimation->Completed.Subscribe([this](){
        std::wcout << "Title animation done!" << std::endl;
        if (auto game = this->weakGame.lock())
        {
            game->ChangeScene(SceneId::Lobby);
        }
    });
}
#pragma endregion

#pragma region Scene
void Title::Showing()
{
    this->titleTextEntranceAnimation->Start();
}

void Title::Hidden()
{
    // Nothing for now.
}

void Title::Update(std::chrono::nanoseconds deltaTime)
{
    Scene::Update(deltaTime);
    // And also update our animation!
    this->titleTextEntranceAnimation->Update(deltaTime);
    this->titleTextExitAnimation->Update(deltaTime);
}
#pragma endregion