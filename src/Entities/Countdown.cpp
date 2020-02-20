#include "Countdown.h"

#include <cmath>
#include <memory>

#pragma region Constructor/Destructor
Countdown::Countdown(
    SDL_Renderer* renderer,
    std::chrono::milliseconds durationMs,
    unsigned short numDigits,
    unsigned short numDecimals
) : 
    renderer(renderer),
    durationMs(durationMs),
    numDecimals(numDecimals)
{
    // Set up format string
    this->displayFormat = L"%0" + 
        std::to_wstring(numDigits) + L"." + 
            std::to_wstring(numDecimals) + L"F";

    // Instantiate text
    this->text = std::make_unique<Text>(
        this->renderer,
        FontFace::Default,
        64,
        SDL_Color{255, 255, 255, 255},
        L"0");
}
#pragma endregion

#pragma region Public methods
void Countdown::Start()
{
    this->remainingTimeMs = this->durationMs;
    this->elapsedTimeMs = std::chrono::milliseconds(1);
    this->running = true;
}

void Countdown::Stop()
{
    this->running = false;
}

double Countdown::GetX()
{
    return this->x;
}

double Countdown::GetY()
{
    return this->y;
}

void Countdown::SetX(double x)
{
    this->x = x;
}

void Countdown::SetY(double y)
{
    this->y = y;
}
#pragma endregion

#pragma region IGameEntity
void Countdown::Draw()
{
    double displaySecond = std::chrono::duration<double>(this->remainingTimeMs)
        .count();
    if ((this->numDecimals == 0) &&
        (this->remainingTimeMs > std::chrono::milliseconds(0)))
    {
        displaySecond = std::floor(displaySecond) + 1.0;
    }
    wchar_t buffer [32];
    const wchar_t* format = this->displayFormat.c_str();
    int cx = swprintf(buffer,
        32,
        format,
        displaySecond);
    std::wstring timerString = std::wstring(buffer);
    this->text->SetContent(timerString);
    this->text->SetX(this->x - (this->text->GetWidth() / 2.0));
    this->text->SetY(this->y - (this->text->GetHeight() / 2.0));
    this->text->Draw();
}

void Countdown::Update(std::chrono::nanoseconds deltaTime)
{
    if (this->running)
    {
        this->elapsedTimeMs += 
            std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
        this->remainingTimeMs = 
            this->durationMs - this->elapsedTimeMs;
        if (this->remainingTimeMs <= std::chrono::milliseconds(0))
        {
            this->remainingTimeMs = std::chrono::milliseconds(0);
            this->running = false;
            this->Completed.Fire();
        }
    }
}
#pragma endregion