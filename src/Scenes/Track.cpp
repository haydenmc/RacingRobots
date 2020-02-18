#include "Track.h"

#include <iostream>

#pragma region Constructor/Destructor
Track::Track(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    Scene(game, sceneBounds)
{
    this->countdown = std::make_unique<StartCountdown>(this->sdlRenderer, 3);
    this->countdown->SetX(this->sceneBounds.x + (this->sceneBounds.w / 2.0));
    this->countdown->SetY(this->sceneBounds.y + (this->sceneBounds.h / 2.0));
    this->countdown->Completed.Subscribe([this]{
        this->StartRace();
    });
}
#pragma endregion

#pragma region Scene
void Track::Showing()
{
    if (auto game = this->weakGame.lock())
    {
        // Fetch lineup
        this->lineup = game->GetRobotLineup();
        // Set the starting lineup positions!
        unsigned int robotCount = this->lineup.size();
        unsigned int startingX = this->sceneBounds.x + this->BORDER_BUFFER;
        unsigned int startingY = this->sceneBounds.y + this->BORDER_BUFFER;
        unsigned int staggerY = (this->sceneBounds.h - (this->BORDER_BUFFER * 2)) / robotCount;
        for (unsigned int i = 0; i < this->lineup.size(); ++i)
        {
            auto& robot = this->lineup.at(i);
            robot->SetX(startingX);
            robot->SetY(startingY + (i * staggerY) + (robot->GetHeight() / 2));
        }
        this->countdown->Start();
    }
    else
    {
        throw std::runtime_error("Track lost reference to Game object.");
    }
}

void Track::Hidden()
{

}

void Track::Draw()
{
    this->Scene::Draw();
    for (auto& robot : this->lineup)
    {
        robot->Draw();
    }
    this->countdown->Draw();
}

void Track::Update(std::chrono::nanoseconds deltaTime)
{
    this->Scene::Update(deltaTime);
    for (auto& robot : this->lineup)
    {
        robot->Update(deltaTime);
    }
    this->countdown->Update(deltaTime);
}
#pragma endregion

#pragma region Track methods
void Track::StartRace()
{
    std::wcout << "Race started!" << std::endl;
    for (auto& robot : this->lineup)
    {
        robot->StartRace();
    }
    this->raceStarted = true;
}
#pragma endregion