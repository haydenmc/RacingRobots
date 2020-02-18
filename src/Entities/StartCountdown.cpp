#include "StartCountdown.h"

#include <memory>

#pragma region Constructor/Destructor
StartCountdown::StartCountdown(
    SDL_Renderer* renderer,
    unsigned int totalSeconds
) : 
    renderer(renderer),
    totalSeconds(totalSeconds)
{
    this->text = std::make_unique<Text>(
        this->renderer,
        FontFace::Default,
        64,
        SDL_Color{255, 255, 255, 255},
        L"0");
}
#pragma endregion

#pragma region Public methods
void StartCountdown::Start()
{
    this->currentSecond = 0;
    this->elapsedTimeMs = std::chrono::milliseconds(1);
    this->running = true;
}

double StartCountdown::GetX()
{
    return this->x;
}

double StartCountdown::GetY()
{
    return this->y;
}

void StartCountdown::SetX(double x)
{
    this->x = x;
}

void StartCountdown::SetY(double y)
{
    this->y = y;
}
#pragma endregion

#pragma region IGameEntity
void StartCountdown::Draw()
{
    if (this->running)
    {
        this->text->Draw();
    }
}

void StartCountdown::Update(std::chrono::nanoseconds deltaTime)
{
    if (this->running)
    {
        this->elapsedTimeMs += 
            std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
        auto remainingTimeMs = 
            std::chrono::seconds(this->totalSeconds) - 
            this->elapsedTimeMs;
        if (remainingTimeMs <= std::chrono::milliseconds(0))
        {
            this->running = false;
            this->Completed.Fire();
        }
        else
        {
            auto displaySecond = static_cast<unsigned int>(
                std::chrono::duration_cast<std::chrono::seconds>(remainingTimeMs)
                .count() + 1);
            if (displaySecond != this->currentSecond)
            {
                wchar_t buffer [8];
                int cx = swprintf(buffer, 8, L"%01d", displaySecond);
                std::wstring timerString = std::wstring(buffer);
                this->text->SetContent(timerString);
                this->text->SetX(this->x - (this->text->GetWidth() / 2.0));
                this->text->SetY(this->y - (this->text->GetHeight() / 2.0));
                this->currentSecond = displaySecond;
            }
        }
    }
}
#pragma endregion