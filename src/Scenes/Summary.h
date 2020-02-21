#pragma once

#include "../Scene.h"

/**
 * @brief Summary is shown after the race to present results.
 */
class Summary : public Scene
{
public:
    Summary(
        std::weak_ptr<Game> game,
        SDL_Rect renderingBounds
    );

    /* Scene */
    void Showing() override;
    void Hidden() override;
    void Draw() override;
    void Update(std::chrono::nanoseconds deltaTime) override;

private:
    std::vector<std::shared_ptr<Robot>> lineup;
    std::vector<std::shared_ptr<Robot>> orderedFinisherListDesc;
};