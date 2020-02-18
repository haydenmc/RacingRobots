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
    this->timerText = std::make_shared<Text>
    (
        this->sdlRenderer,
        FontFace::Default,
        48,
        SDL_Color{255, 255, 255, 255},
        L"00:00"
    );
    // Position top left in the scene
    this->headerText->SetX(this->sceneBounds.x + 48.0);
    this->headerText->SetY(this->sceneBounds.y + 48.0);
    this->timerText->SetX(this->sceneBounds.w - 
        this->timerText->GetWidth() - 48.0);
    this->timerText->SetY(this->sceneBounds.y + 48.0);
    this->gameEntities.push_back(this->headerText);
    this->gameEntities.push_back(this->timerText);
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

    // Reset the timer
    this->elapsedTimeMs = std::chrono::milliseconds(0);
    this->lastTimerUpdateMs = std::chrono::milliseconds(0);
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

    // Update elapsed time
    auto deltaTimeMs = 
        std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
    this->elapsedTimeMs += deltaTimeMs;

    // Update timer text
    if (this->lastTimerUpdateMs.count() == 0 || 
        this->elapsedTimeMs - this->lastTimerUpdateMs > std::chrono::seconds(1))
    {
        auto timeRemainingSeconds =
            (std::chrono::seconds(Game::LobbyTimeSeconds) - 
            std::chrono::duration_cast<std::chrono::seconds>(
                this->elapsedTimeMs)).count();
        if (timeRemainingSeconds < 0)
        {
            timeRemainingSeconds = 0;
            // TODO: start fade-out/transition
            if (auto game = this->weakGame.lock())
            {
                game->ChangeScene(SceneId::Track);
            }
            else
            {
                throw std::runtime_error(
                    "Lobby lost reference to Game object.");
            }
        }
        unsigned int timerMinutes = timeRemainingSeconds / 60u;
        unsigned int timerSeconds =
            timeRemainingSeconds - (timerMinutes * 60u);
        wchar_t buffer [32];
        int cx = swprintf(buffer, 32, L"%02d:%02d", timerMinutes, timerSeconds);
        std::wstring timerString = std::wstring(buffer);
        this->timerText->SetContent(timerString);
        this->lastTimerUpdateMs = this->elapsedTimeMs;
    }

    for (auto& robot : this->robotLineup)
    {
        robot->Update(deltaTime);
    }
}
#pragma endregion