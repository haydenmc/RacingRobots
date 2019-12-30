#pragma once

#include <chrono>

/**
 * @brief Represents a game entity that supports drawing and updating
 *        game state over simulation time.
 */
class IGameEntity
{
public:
    /**
     * @brief Requests that the entity draw to its renderer.
     */
    virtual void Draw() = 0;

    /**
     * @brief Requests that the entity update its game state
     *        relative to the time that has passed.
     * 
     * @param deltaTime The time that has passed since the last
     *                  game state update.
     */
    virtual void Update(std::chrono::nanoseconds deltaTime) = 0;
};