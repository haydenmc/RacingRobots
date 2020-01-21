#pragma once

#include "IGameEntity.h"
#include "SDL.h"

#include <memory>
#include <vector>

/**
 * @brief A Scene represents a particular set of game objects that exist
 *        at once, usually associated with a specific sub-set of game state.
 */
class Scene : public IGameEntity
{
public:
    /* Constructor/Destructor */
    Scene(
        SDL_Renderer* sdlRenderer,
        SDL_Rect sceneBounds
    );
    Scene(
        SDL_Renderer* sdlRenderer,
        SDL_Rect sceneBounds,
        std::vector<std::shared_ptr<IGameEntity>> gameEntities
    );

    /* IGameEntity */
    virtual void Draw() override;
    virtual void Update(std::chrono::nanoseconds deltaTime) override;

protected:
    SDL_Renderer* sdlRenderer;
    SDL_Rect sceneBounds;
    std::vector<std::shared_ptr<IGameEntity>> gameEntities;
};