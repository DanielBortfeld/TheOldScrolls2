// Game Logic Test - Daniel Bortfeld 2018
#include "UpdateManager.h"
#include "GameObject.h"

void UpdateManager::UpdateAllGameObjects(sf::Time const& deltaTime)
{
	for (auto& gameObject : gameObjects)
	{
		if (!gameObject.expired())
		{
			gameObject.lock()->Update(deltaTime);
		}
	}
}

void UpdateManager::AddGameObject(std::weak_ptr<GameObject> const& gameObject)
{
	if (!gameObject.expired())
	{
		gameObjects.push_back(gameObject);
	}
}
