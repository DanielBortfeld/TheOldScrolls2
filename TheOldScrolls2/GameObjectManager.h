// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef GAMEOBJECT_MANAGER_H
#define GAMEOBJECT_MANAGER_H

#include "Singleton.h"

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>

class Enemy;
class Player;
class Trap;
class UIText;

class GameObjectManager : public Singleton<GameObjectManager>
{
private:

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Trap>> traps;
	std::vector<std::shared_ptr<UIText>> texts;

public:

	GameObjectManager() = default;
	~GameObjectManager() = default;

	void AddPlayer(sf::Vector2f const& position);
	void AddEnemy(sf::Vector2f const& position);
	void AddTrap(sf::Vector2f const& position);
	std::weak_ptr<UIText> AddUIText(sf::String const& text, sf::Vector2f const & screenPosition, sf::Color const & color, sf::RenderWindow const& window);

	void RemovePlayer();
	void RemoveEnemy(Enemy* enemy);
	void RemoveText(UIText* text);

	std::weak_ptr<Player> GetPlayer() const;

	bool IsPlayerAlive() const;
	bool AreEnemiesAlive() const;
};

#endif // !GAMEOBJECT_MANAGER_H
