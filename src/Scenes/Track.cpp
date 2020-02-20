#include "Track.h"

#include "SDL2_gfxPrimitives.h"
#include "../Utilities/PlaceStrings.h"

#include <iostream>

#pragma region Constructor/Destructor
Track::Track(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    Scene(game, sceneBounds)
{
    this->startCountdown = std::make_unique<Countdown>(
        // Renderer
        this->sdlRenderer,
        // Duration in milliseconds
        std::chrono::milliseconds(this->START_COUNTDOWN_DURATION_MS), 
        // Min width to pad with zeroes
        1,
        // Num decimals
        0
    );
    this->startCountdown->SetX(this->sceneBounds.x + (this->sceneBounds.w / 2.0));
    this->startCountdown->SetY(this->sceneBounds.y + (this->sceneBounds.h / 2.0));
    this->startCountdown->Completed.Subscribe([this]{
        this->StartRace();
    });

    this->endCountdown = std::make_unique<Countdown>(
        // Renderer
        this->sdlRenderer,
        // Duration in milliseconds
        std::chrono::milliseconds(this->END_COUNTDOWN_DURATION_MS), 
        // Min width to pad with zeroes
        2,
        // Num decimals
        2
    );
    this->endCountdown->SetX(this->sceneBounds.x + (this->sceneBounds.w / 2.0));
    this->endCountdown->SetY(this->sceneBounds.y + (this->sceneBounds.h / 2.0));
    this->endCountdown->Completed.Subscribe([this]{
        this->EndRace();
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
        this->startCountdown->Start();
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

    if (!this->raceStarted)
    {
        this->startCountdown->Draw();
    }

    if (this->endCountdownStarted)
    {
        this->endCountdown->Draw();
    }

    // Draw a finish line
    thickLineRGBA(
        this->sdlRenderer,
        this->sceneBounds.x + this->sceneBounds.w - this->FINISH_BUFFER,
        this->sceneBounds.y,
        this->sceneBounds.x + this->sceneBounds.w - this->FINISH_BUFFER,
        this->sceneBounds.y + this->sceneBounds.h,
        this->FINISH_LINE_THICKNESS,
        std::get<0>(this->FINISH_LINE_COLOR),
        std::get<1>(this->FINISH_LINE_COLOR),
        std::get<2>(this->FINISH_LINE_COLOR),
        std::get<3>(this->FINISH_LINE_COLOR)
    );
}

void Track::Update(std::chrono::nanoseconds deltaTime)
{
    this->Scene::Update(deltaTime);
    for (auto& robot : this->lineup)
    {
        robot->Update(deltaTime);

        // Has this robot already been marked as having finished?
        if (this->finishedRobots.find(robot) == this->finishedRobots.end())
        {
            // Check if they have actually finished and process them
            if (this->HasRobotFinished(robot))
            {
                if (!this->endCountdownStarted)
                {
                    this->endCountdown->Start();
                    this->endCountdownStarted = true;
                }

                this->finishedRobots.insert(robot);
                this->orderedFinisherListDesc.push_back(robot);

                std::wcout << robot->GetName() << " finishes in " <<
                    PlaceStrings::GetPlaceString(
                        this->orderedFinisherListDesc.size()) << " place!" <<
                    std::endl;

                if (this->finishedRobots.size() >= this->lineup.size())
                {
                    std::wcout << L"All robots have finished!" << std::endl;
                    this->EndRace();
                }
            }
        }
    }
    this->startCountdown->Update(deltaTime);
    this->endCountdown->Update(deltaTime);
}
#pragma endregion

#pragma region Track methods
void Track::StartRace()
{
    std::wcout << "Race started!" << std::endl;
    this->finishedRobots.clear();
    this->orderedFinisherListDesc.clear();
    this->endCountdownStarted = false;
    for (auto& robot : this->lineup)
    {
        robot->StartRacing();
    }
    this->raceStarted = true;
}

void Track::EndRace()
{
    std::wcout << "Race ended!" << std::endl;
    for (auto& robot : this->lineup)
    {
        robot->StopRacing();
    }
    this->endCountdown->Stop();

    // Commit race results
    if (auto game = this->weakGame.lock())
    {
        game->CommitRaceResults(this->orderedFinisherListDesc);
    }
    else
    {
        throw std::runtime_error("Track lost reference to Game object.");
    }
    
}

bool Track::HasRobotFinished(const std::shared_ptr<Robot> robot)
{
    return ((robot->GetX() + robot->GetWidth()) > 
        (this->sceneBounds.x + this->sceneBounds.w - this->FINISH_BUFFER));
}
#pragma endregion