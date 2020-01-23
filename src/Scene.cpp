#include "Scene.h"

#pragma region Constructor/Destructor
Scene::Scene(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds
) : 
    weakGame(game),
    sceneBounds(sceneBounds)
{
    if (auto gamePtr = game.lock())
    {
        this->sdlRenderer = gamePtr->GetSDLRenderer();
    }
}

Scene::Scene(
    std::weak_ptr<Game> game,
    SDL_Rect sceneBounds,
    std::vector<std::shared_ptr<IGameEntity>> gameEntities
) : 
    sceneBounds(sceneBounds),
    gameEntities(gameEntities)
{
    if (auto gamePtr = game.lock())
    {
        this->sdlRenderer = gamePtr->GetSDLRenderer();
    }
}
#pragma endregion

#pragma region IGameEntity
void Scene::Draw()
{
    for (auto& entity : this->gameEntities)
    {
        entity->Draw();
    }
}

void Scene::Update(std::chrono::nanoseconds deltaTime)
{
    for (auto& entity : this->gameEntities)
    {
        entity->Update(deltaTime);
    }
}
#pragma endregion