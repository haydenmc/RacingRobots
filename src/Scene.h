#pragma once

#include "IGameEntity.h"

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
    Scene();
    Scene(std::vector<std::shared_ptr<IGameEntity>> gameEntities);

    /* IGameEntity */
    virtual void Draw() override;
    virtual void Update(std::chrono::nanoseconds deltaTime) override;

protected:
    std::vector<std::shared_ptr<IGameEntity>> gameEntities;
};