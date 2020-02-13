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
    double endX = this->sceneBounds.x + 48.0;
    double deltaX = endX - startX;
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
    this->titleTextAnimation = std::make_shared<Tweener<double>>(
        &EasingFunctions::QuartOutEase<double>,
        [this, startX, deltaX](double value)
        {
            // Bring into view, left-aligned
            auto newX = startX + (deltaX * value);
            this->titleText->SetX(newX);
        },
        0.0,
        1.0,
        std::chrono::milliseconds(2000)
    );

    auto animCompleteCallback = [this](){
        std::wcout << "Title animation done!" << std::endl;
        if (auto game = this->weakGame.lock())
        {
            game->ChangeScene(SceneId::Lobby);
        }
    };

    this->titleTextAnimation->Completed.Subscribe(animCompleteCallback);
}
#pragma endregion

#pragma region Scene
void Title::Showing()
{
    this->titleTextAnimation->Start();
}

void Title::Hidden()
{
    // Nothing for now.
}

void Title::Update(std::chrono::nanoseconds deltaTime)
{
    Scene::Update(deltaTime);
    // And also update our animation!
    this->titleTextAnimation->Update(deltaTime);
}
#pragma endregion