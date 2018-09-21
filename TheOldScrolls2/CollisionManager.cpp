// Game Logic Test - Daniel Bortfeld 2018
#include "CollisionManager.h"
#include "GameObject.h"

void CollisionManager::CheckCollisions() const
{
	auto CheckAgainst = [&](auto const& gameObjectA, auto const& vectorB)
	{
		if (!gameObjectA.expired())
		{
			auto gameObjectAPtr = gameObjectA.lock();

			for (auto& gameObjectB : vectorB)
			{
				if (!gameObjectB.expired())
				{
					auto gameObjectBPtr = gameObjectB.lock();

					if (gameObjectAPtr != gameObjectBPtr)
					{
						if (gameObjectAPtr->GetBounds().intersects(gameObjectBPtr->GetBounds()))
						{
							gameObjectAPtr->OnCollisionEnter(gameObjectBPtr);
						}
					}
				}
			}
		}
	};

	for (auto& gameObjectA : movableGameObjects)
	{
		CheckAgainst(gameObjectA, movableGameObjects);
		CheckAgainst(gameObjectA, stationaryGameObjects);
	}
}

void CollisionManager::AddMovableGameObject(std::weak_ptr<GameObject> const& gameObject)
{
	if (!gameObject.expired())
	{
		movableGameObjects.push_back(gameObject);
	}
}

void CollisionManager::AddStationaryGameObject(std::weak_ptr<GameObject> const& gameObject)
{
	if (!gameObject.expired())
	{
		stationaryGameObjects.push_back(gameObject);
	}
}
