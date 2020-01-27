#include "Lobby.h"

#include <stdexcept>

#pragma region Constructor/Destructor
Lobby::Lobby(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    Scene(game, sceneBounds)
{
    // Generate text
    this->headerText = std::make_shared<Text>
    (
        this->sdlRenderer,
        FontFace::Default,
        32,
        SDL_Color{255, 255, 255, 255},
        "Starting Lineup"
    );
    // Position top center in the scene
    this->headerText->SetX(
        (this->sceneBounds.w / 2) - 
        (this->headerText->GetWidth() / 2) + 
        this->sceneBounds.x
    );
    this->headerText->SetY(0);
    this->gameEntities.push_back(this->headerText);
}
#pragma endregion

#pragma region Scene
void Lobby::Showing()
{
    // Generate a new roster of racers!
    auto game = this->weakGame.lock();
    if (!game)
    {
        throw std::runtime_error("Reference to Game was lost unexpectedly!");
    }

    game->GenerateNewLineup();
    this->robotLineup = game->GetRobotLineup();

    // We'll position the lineup about 1/2 of the way down the screen
    double yPos = (this->sceneBounds.h / 2.0) + this->sceneBounds.y;
    double xBuffer = 128;
    double xStagger = 
            (this->sceneBounds.w - (xBuffer * 2)) / 
            (static_cast<double>(this->robotLineup.size() - 1));
    for (unsigned int i = 0; i < this->robotLineup.size(); ++i)
    {
        auto& robot = this->robotLineup.at(i);
        robot->SetX(
            xBuffer + 
            (xStagger * static_cast<double>(i)) - 
            (robot->GetWidth() / 2.0)
        );
        robot->SetY(yPos);
    }
}

void Lobby::Hidden()
{

}

void Lobby::Draw()
{
    this->Scene::Draw();
    for (auto& robot : this->robotLineup)
    {
        robot->Draw();
    }
}

void Lobby::Update(std::chrono::nanoseconds deltaTime)
{
    this->Scene::Update(deltaTime);
    for (auto& robot : this->robotLineup)
    {
        robot->Update(deltaTime);
    }
}
#pragma endregion