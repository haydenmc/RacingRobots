/**
 * @file Tween.h
 * @author Hayden McAfee (hayden@outlook.com)
 * @brief A header-only library to enable simple tweening of values
 */

#pragma once

#include <chrono>
#include <functional>
#include <iostream>

#pragma region Easing Functions
/**
 * @brief Linear easing function
 */
class LinearEasingFunction
{
public:
    template<typename T>
    static T EasingValue(
        std::chrono::milliseconds currentTimeMs,
        T beginningValue,
        T changeInValue,
        std::chrono::milliseconds durationMs
    )
    {
        double durationPercentage = (currentTimeMs.count() / static_cast<double>(durationMs.count()));
        return (changeInValue * durationPercentage) + beginningValue;
    };
};

class QuartOutEasingFunction
{
public:
    template<typename T>
    static T EasingValue(
        std::chrono::milliseconds currentTimeMs,
        T beginningValue,
        T changeInValue,
        std::chrono::milliseconds durationMs
    )
    {
        long long currentTime = currentTimeMs.count();
        long long duration = durationMs.count();
        double durationPercentage = (currentTime / static_cast<double>(duration));
        double inverseDurationPercentage = durationPercentage - 1;
        return -changeInValue * (std::pow(inverseDurationPercentage, 4) - 1) + beginningValue;
    };
};
#pragma endregion

/**
 * @brief Simple static class to tween properties on game entities
 */
template<typename EasingFunction, typename T>
class Tweener
{
private:
    std::function<void(T)> valueSetter;
    bool isRunning = false;
    T beginningValue;
    T changeInValue;
    std::chrono::milliseconds durationMs;
    std::chrono::milliseconds elapsedTimeMs;

public:
    Tweener(
        std::function<void(T)> valueSetter,
        T beginningValue,
        T changeInValue,
        std::chrono::milliseconds durationMs
    ) : 
        valueSetter(valueSetter),
        beginningValue(beginningValue),
        changeInValue(changeInValue),
        durationMs(durationMs)
    { }

    void Start()
    {
        this->elapsedTimeMs = std::chrono::milliseconds(0);
        this->isRunning = true;
    }

    void Update(std::chrono::nanoseconds deltaTime)
    {
        if (this->isRunning)
        {
            auto deltaTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
            this->elapsedTimeMs += deltaTimeMs;
            T newValue = EasingFunction::EasingValue<T>(
                this->elapsedTimeMs,
                this->beginningValue,
                this->changeInValue,
                this->durationMs
            );
            this->valueSetter(newValue);
            
            if (this->elapsedTimeMs >= this->durationMs)
            {
                this->valueSetter(this->beginningValue + this->changeInValue);
                this->isRunning = false;
                // TODO: Finished event
            }
        }
    }
};