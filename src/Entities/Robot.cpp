#include "Robot.h"

#include <iostream>

std::random_device Robot::RANDOM_DEVICE = std::random_device();

Robot::Robot(
    SDL_Renderer* renderer,
    std::wstring name,
    std::string imagePath,
    RobotTraits traits
) : 
    Graphic(renderer, imagePath),
    name(name),
    traits(traits)
{
    std::wcout << L"Constructing robot '" << name << L"'" << std::endl;
    this->recalculateTraits();
}

void Robot::StartRacing()
{
    std::wcout << this->name << " starting race!" << std::endl;
    this->isRacing = true;
}

void Robot::StopRacing()
{
    this->isRacing = false;
}

std::wstring Robot::GetName()
{
    return this->name;
}

double Robot::GetX()
{
    return this->x;
}

double Robot::GetY()
{
    return this->y;
}

unsigned int Robot::GetWins()
{
    return this->totalWins;
}

void Robot::SetWins(unsigned int wins)
{
    this->totalWins = wins;
}

unsigned int Robot::GetLosses()
{
    return this->totalLosses;
}

void Robot::SetLosses(unsigned int losses)
{
    this->totalLosses = losses;
}

void Robot::Update(std::chrono::nanoseconds deltaTime)
{
    auto deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

    if (this->isRacing)
    {
        // Calculate sprinting/stamina/speeds...
        if (this->isSprinting)
        {
            if (this->currentVelocity < this->maxVelocity)
            {
                this->currentVelocity += this->acceleration * deltaTimeMs.count();
            }
            else
            {
                this->currentVelocity = this->maxVelocity;
            }

            if (this->currentStamina > 0)
            {
                this->currentStamina -= this->STAMINA_BURN_RATE * deltaTimeMs.count();
            }
            else
            {
                this->isSprinting = false;
            }
        }
        else
        {
            this->currentVelocity = this->minVelocity;
            this->currentStamina += this->staminaRechargeRate * deltaTimeMs.count();
            if (this->currentStamina >= this->maxStamina)
            {
                this->isSprinting = true;
            }
        }

        // Apply speed!
        this->x += this->currentVelocity * deltaTimeMs.count();
    }
}

void Robot::recalculateTraits()
{
    std::mt19937 generator(this->RANDOM_DEVICE());

    this->minVelocity = std::uniform_real_distribution<double>(
        std::get<0>(this->traits.minVelocityWindow),
        std::get<1>(this->traits.minVelocityWindow)
    )(generator);

    this->maxVelocity = std::uniform_real_distribution<double>(
        std::get<0>(this->traits.maxVelocityWindow),
        std::get<1>(this->traits.maxVelocityWindow)
    )(generator);

    this->acceleration = std::uniform_real_distribution<double>(
        std::get<0>(this->traits.accelerationWindow),
        std::get<1>(this->traits.accelerationWindow)
    )(generator);

    this->maxStamina = std::uniform_real_distribution<double>(
        std::get<0>(this->traits.maxStaminaWindow),
        std::get<1>(this->traits.maxStaminaWindow)
    )(generator);

    this->staminaRechargeRate = std::uniform_real_distribution<double>(
        std::get<0>(this->traits.staminaRechargeRateWindow),
        std::get<1>(this->traits.staminaRechargeRateWindow)
    )(generator);

    std::wcout << this->name << " traits: " << std::endl <<
        "Min Velocity: " << this->minVelocity << std::endl <<
        "Max Velocity: " << this->maxVelocity << std::endl <<
        "Acceleration: " << this->acceleration << std::endl <<
        "Max Stamina: " << this->maxStamina << std::endl <<
        "Stamina Recharge Rate: " << this->staminaRechargeRate << std::endl;
}