#pragma once

#include "Graphic.h"

#include <chrono>
#include <random>
#include <tuple>

struct RobotTraits
{
    // TODO: Add distributions to each trait
    // The robot's minimum non-sprint speed
    std::tuple<double, double> minVelocityWindow;
    // The fastest this robot can go
    std::tuple<double, double> maxVelocityWindow;
    // Robot's acceleration when increasing speed
    std::tuple<double, double> accelerationWindow;
    // The maximum amount of stamina
    std::tuple<double, double> maxStaminaWindow;
    // Rate at which stamina recharges
    std::tuple<double, double> staminaRechargeRateWindow;
};

class Robot : public Graphic
{
public:
    Robot(
        SDL_Renderer* renderer,
        std::wstring name,
        std::string imagePath,
        RobotTraits traits
    );
    
    void StartRacing();
    void StopRacing();
    std::wstring GetName();
    double GetX();
    double GetY();
    unsigned int GetWins();
    void SetWins(unsigned int wins);
    unsigned int GetLosses();
    void SetLosses(unsigned int losses);

    /* Graphic */
    void Update(std::chrono::nanoseconds deltaTime) override;
private:
    void recalculateTraits();

    /* Statics */
    static std::random_device RANDOM_DEVICE;
    static constexpr double STAMINA_BURN_RATE = 0.01;

    /* Robot info */
    std::wstring name;
    unsigned int totalWins = 0;
    unsigned int totalLosses = 0;

    /* Racing traits */
    RobotTraits traits;
    double minVelocity;
    double maxVelocity;
    double acceleration;
    double maxStamina;
    double staminaRechargeRate;

    /* Racing state */
    double currentVelocity;
    double currentStamina;
    bool isSprinting = false;
    bool isRacing = false;
};
