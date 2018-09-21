// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

#include "Singleton.h"

#include <vector>
#include <memory>
#include <SFML\System\Clock.hpp>

class GameObject;

class UpdateManager : public Singleton<UpdateManager>
{
private:

	std::vector<std::weak_ptr<GameObject>> gameObjects;

public:

	UpdateManager() = default;
	~UpdateManager() = default;
	void UpdateAllGameObjects(sf::Time const& deltaTime);
	void AddGameObject(std::weak_ptr<GameObject> const& gameObject);
};

#endif // !UPDATE_MANAGER_H
