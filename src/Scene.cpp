#include "Scene.h"

#pragma region Constructor/Destructor
Scene::Scene()
{ }

Scene::Scene(std::vector<std::shared_ptr<IGameEntity>> gameEntities) : 
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