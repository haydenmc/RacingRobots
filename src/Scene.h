#pragma once

#include "Game.h"
#include "IGameEntity.h"
#include "SDL.h"

#include <memory>
#include <vector>

class Game; // forward declare since these are circular dependencies

/**
 * @brief A Scene represents a particular set of game objects that exist
 *        at once, usually associated with a specific sub-set of game state.
 */
class Scene : public IGameEntity
{
public:
    /* Constructor/Destructor */
    Scene(
        std::weak_ptr<Game> game,
        SDL_Rect sceneBounds
    );
    Scene(
        std::weak_ptr<Game> game,
        SDL_Rect sceneBounds,
        std::vector<std::shared_ptr<IGameEntity>> gameEntities
    );

    /* IGameEntity */
    virtual void Draw() override;
    virtual void Update(std::chrono::nanoseconds deltaTime) override;

protected:
    std::weak_ptr<Game> weakGame;
    SDL_Renderer* sdlRenderer;
    SDL_Rect sceneBounds;
    std::vector<std::shared_ptr<IGameEntity>> gameEntities;
};