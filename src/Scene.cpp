#include "Scene.h"

#pragma region Constructor/Destructor
Scene::Scene(
    SDL_Renderer* sdlRenderer,
    SDL_Rect sceneBounds
) : 
    sdlRenderer(sdlRenderer),
    sceneBounds(sceneBounds)
{ }

Scene::Scene(
    SDL_Renderer* sdlRenderer,
    SDL_Rect sceneBounds,
    std::vector<std::shared_ptr<IGameEntity>> gameEntities
) : 
    sdlRenderer(sdlRenderer),
    sceneBounds(sceneBounds),
    gameEntities(gameEntities)
{ }
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