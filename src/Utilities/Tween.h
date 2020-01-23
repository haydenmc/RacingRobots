/**
 * @file Tween.h
 * @author Hayden McAfee (hayden@outlook.com)
 * @brief A header-only library to enable simple tweening of values
 */

#pragma once

#include "Utilities/Event.h"

#include <chrono>
#include <functional>
#include <iostream>

#pragma region Easing Functions
/**
 * @brief Static class to contain easing functions
 */
class EasingFunctions
{
public:
    /**
     * Linear easing function
     */
    template<typename T>
    static T LinearEase(
        std::chrono::milliseconds currentTimeMs,
        T beginningValue,
        T changeInValue,
        std::chrono::milliseconds durationMs
    )
    {
        double durationPercentage = (currentTimeMs.count() / static_cast<double>(durationMs.count()));
        return (changeInValue * durationPercentage) + beginningValue;
    };

    /**
     * Quartic easing out function
     */
    template<typename T>
    static T QuartOutEase(
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
template<typename T>
class Tweener
{
private:
    std::function<
        T(
            std::chrono::milliseconds currentTimeMs,
            T beginningValue,
            T changeInValue,
            std::chrono::milliseconds durationMs
        )
    > easingFunction;
    std::function<void(T)> valueSetter;
    bool isRunning = false;
    T beginningValue;
    T changeInValue;
    std::chrono::milliseconds durationMs;
    std::chrono::milliseconds elapsedTimeMs;

public:
    Event<> Completed;

    Tweener(
        std::function<
            T(
                std::chrono::milliseconds currentTimeMs,
                T beginningValue,
                T changeInValue,
                std::chrono::milliseconds durationMs
            )
        > easingFunction,
        std::function<void(T)> valueSetter,
        T beginningValue,
        T changeInValue,
        std::chrono::milliseconds durationMs
    ) : 
        easingFunction(easingFunction),
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
            T newValue = this->easingFunction(
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
                this->Completed.Fire();
            }
        }
    }
};