#include "Track.h"

#include <iostream>

#pragma region Constructor/Destructor
Track::Track(
    SDL_Renderer* renderer,
    SDL_Rect renderingBounds,
    std::vector<std::shared_ptr<Robot>> robots
) : 
    renderer(renderer),
    renderingBounds(renderingBounds),
    robots(robots)
{
    std::wcout << "Constructing track..." << std::endl;

    // Add robots to game entities
    for (auto& robot : this->robots)
    {
        auto robotGameEntity = std::static_pointer_cast<IGameEntity>(robot);
        this->gameEntities.push_back(robotGameEntity);
    }

    // Set the starting lineup positions!
    unsigned int robotCount = this->robots.size();
    unsigned int startingX = this->renderingBounds.x + this->BORDER_BUFFER;
    unsigned int startingY = this->renderingBounds.y + this->BORDER_BUFFER;
    unsigned int staggerY = (this->renderingBounds.h - (this->BORDER_BUFFER * 2)) / robotCount;
    for (unsigned int i = 0; i < this->robots.size(); ++i)
    {
        auto& robot = this->robots.at(i);
        robot->SetX(startingX);
        robot->SetY(startingY + (i * staggerY) + (robot->GetHeight() / 2));
    }
}
#pragma endregion

#pragma region Track methods
void Track::StartRace()
{
    std::wcout << "Race started!" << std::endl;
    for (auto& robot : this->robots)
    {
        robot->StartRace();
    }
    this->raceStarted = true;
}
#pragma endregion