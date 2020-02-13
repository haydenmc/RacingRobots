#include "StatCard.h"

#include "SDL2_gfxPrimitives.h"

#include <stdexcept>

StatCard::StatCard(
    SDL_Renderer* renderer,
    std::weak_ptr<Robot> robot
) : 
    sdlRenderer(renderer),
    weakRobot(robot)
{
    auto robotRef = robot.lock();
    if (!robotRef)
    {
        throw std::runtime_error("Reference to Robot was lost unexpectedly!");
    }

    // Set up text
    this->nameText = std::make_unique<Text>
    (
        this->sdlRenderer,
        FontFace::Default,
        16,
        SDL_Color{255, 255, 255, 255},
        robotRef->GetName()
    );
}

double StatCard::GetX()
{
    return this->x;
}

double StatCard::GetY()
{
    return this->y;
}

void StatCard::SetX(double x)
{
    this->x = x;
}

void StatCard::SetY(double y)
{
    this->y = y;
}

double StatCard::GetWidth()
{
    return this->width;
}

double StatCard::GetHeight()
{
    return this->height;
}

void StatCard::SetWidth(double width)
{
    this->width = width;
}

void StatCard::SetHeight(double height)
{
    this->height = height;
}

void StatCard::Draw()
{
    // draw frame starting at (x,y)
    // top line
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x + this->cornerLength),
        static_cast<int16_t>(this->y),
        static_cast<int16_t>(this->x + this->width),
        static_cast<int16_t>(this->y),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );
    // right line
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x + this->width),
        static_cast<int16_t>(this->y),
        static_cast<int16_t>(this->x + this->width),
        static_cast<int16_t>(this->y + this->height - this->cornerLength),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );
    // bottom right corner
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x + this->width),
        static_cast<int16_t>(this->y + this->height - this->cornerLength),
        static_cast<int16_t>(this->x + this->width - this->cornerLength),
        static_cast<int16_t>(this->y + this->height),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );
    // bottom line
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x + this->width - this->cornerLength),
        static_cast<int16_t>(this->y + this->height),
        static_cast<int16_t>(this->x),
        static_cast<int16_t>(this->y + this->height),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );
    // left line
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x),
        static_cast<int16_t>(this->y + this->height),
        static_cast<int16_t>(this->x),
        static_cast<int16_t>(this->y + this->cornerLength),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );
    // top left corner
    thickLineRGBA
    (
        this->sdlRenderer,
        static_cast<int16_t>(this->x),
        static_cast<int16_t>(this->y + this->cornerLength),
        static_cast<int16_t>(this->x + this->cornerLength),
        static_cast<int16_t>(this->y),
        static_cast<uint8_t>(this->borderWidth),
        std::get<0>(this->borderColor),
        std::get<1>(this->borderColor),
        std::get<2>(this->borderColor),
        std::get<3>(this->borderColor)
    );

    // Draw robot
    if (auto robot = this->weakRobot.lock())
    {
        robot->SetX(
            this->x +
            (this->GetWidth() / 2) -
            (robot->GetWidth() / 2)
        );
        robot->SetY(this->y + 32.0);
        robot->Draw();
    }

    // Draw text
    this->nameText->SetX(
        this->x + 
        (this->GetWidth() / 2) -
        (this->nameText->GetWidth() / 2)
    );
    this->nameText->SetY(this->y + 112.0);
    this->nameText->Draw();

}

void StatCard::Update(std::chrono::nanoseconds deltaTime)
{ }