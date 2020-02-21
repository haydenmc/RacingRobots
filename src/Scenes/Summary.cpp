#include "Summary.h"
#include "Text.h"
#include "Utilities/PlaceStrings.h"

#include <stdexcept>

#pragma region Constructor/Destructor
Summary::Summary(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    Scene(game, sceneBounds)
{ }
#pragma endregion

#pragma region Scene
void Summary::Showing()
{
    this->Scene::Showing();

    this->gameEntities.clear();

    // Fetch latest rankings
    if (auto game = this->weakGame.lock())
    {
        this->lineup = game->GetRobotLineup();
        this->orderedFinisherListDesc = game->GetLastRaceResults();

        if (this->orderedFinisherListDesc.size() > 0)
        {
            // Show winner
            const auto& winner = this->orderedFinisherListDesc.at(0);
            auto winnerHeaderText = std::make_shared<Text>(
                this->sdlRenderer,
                FontFace::Default,
                64,
                SDL_Color{255, 255, 255, 255},
                L"WINNER:"
            );
            winnerHeaderText->SetX(
                this->sceneBounds.x + 
                (this->sceneBounds.w / 2.0) - 
                (winnerHeaderText->GetWidth() / 2.0)
            );
            winnerHeaderText->SetY(32);
            this->gameEntities.push_back(winnerHeaderText);

            auto winnerNameText = std::make_shared<Text>(
                this->sdlRenderer,
                FontFace::Default,
                36,
                SDL_Color{255, 255, 255, 255},
                winner->GetName()
            );
            winnerNameText->SetX(
                this->sceneBounds.x + 
                (this->sceneBounds.w / 2.0) - 
                (winnerNameText->GetWidth() / 2.0)
            );
            winnerNameText->SetY(32 + winnerHeaderText->GetHeight());
            this->gameEntities.push_back(winnerNameText);

            // Now add the rest of the finishers
            for (unsigned int i = 1;
                i < this->orderedFinisherListDesc.size(); ++i)
            {
                const auto& robot = this->orderedFinisherListDesc.at(i);
                unsigned int placeNumber = i + 1;
                auto placeText = std::make_shared<Text>(
                    this->sdlRenderer,
                    FontFace::Default,
                    26,
                    SDL_Color{255, 255, 255, 255},
                    PlaceStrings::GetPlaceString(placeNumber) + 
                        L". " + robot->GetName()
                );
                placeText->SetX(
                    this->sceneBounds.x + 
                    (this->sceneBounds.w / 2.0) - 
                    (placeText->GetWidth() / 2.0)
                );
                placeText->SetY(128 + (i * 48));
                this->gameEntities.push_back(placeText);
            }
        }
    }
    else
    {
        throw std::runtime_error("Summary Scene could not get reference "
            "to Game");
    }
    
}

void Summary::Hidden()
{
    this->Scene::Hidden();
}

void Summary::Draw()
{
    this->Scene::Draw();
}

void Summary::Update(std::chrono::nanoseconds deltaTime)
{
    this->Scene::Update(deltaTime);
}
#pragma endregion