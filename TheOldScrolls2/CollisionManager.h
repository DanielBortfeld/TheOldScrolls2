// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include <memory>
#include "Singleton.h"

class GameObject;

class CollisionManager : public Singleton<CollisionManager>
{
private:

	std::vector<std::weak_ptr<GameObject>> movableGameObjects;
	std::vector<std::weak_ptr<GameObject>> stationaryGameObjects;

public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void CheckCollisions() const;
	void AddMovableGameObject(std::weak_ptr<GameObject> const& gameObject);
	void AddStationaryGameObject(std::weak_ptr<GameObject> const& gameObject);
};

#endif // !COLLISION_MANAGER_H
