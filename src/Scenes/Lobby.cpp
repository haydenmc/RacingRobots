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
        48,
        SDL_Color{255, 255, 255, 255},
        L"Starting Lineup"
    );
    // Position top left in the scene
    this->headerText->SetX(this->sceneBounds.x + 48.0);
    this->headerText->SetY(this->sceneBounds.y + 48.0);
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
    double xBuffer = 48.0;
    double cardMargin = 32.0;
    double cardWidth = 
        (this->sceneBounds.w - (xBuffer * 2) -
            (cardMargin * (this->robotLineup.size() - 1))) / 
        (this->robotLineup.size());

    // Generate stat cards for each robot!
    this->statCards.clear();
    for (unsigned int i = 0; i < this->robotLineup.size(); ++i)
    {
        const auto& robot = this->robotLineup.at(i);
        auto statCard = std::make_shared<StatCard>(this->sdlRenderer, robot);
        statCard->SetWidth(cardWidth);
        statCard->SetX(
            xBuffer + 
            (cardWidth * static_cast<double>(i)) +
            (cardMargin * static_cast<double>(i))
        );
        statCard->SetY(
            yPos - (statCard->GetHeight() / 2.0)
        );
        this->statCards.push_back(statCard);
    }
}

void Lobby::Hidden()
{

}

void Lobby::Draw()
{
    this->Scene::Draw();
    for (auto& statCard : this->statCards)
    {
        statCard->Draw();
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