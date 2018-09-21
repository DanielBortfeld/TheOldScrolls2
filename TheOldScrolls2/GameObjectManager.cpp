// Game Logic Test - Daniel Bortfeld 2018
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "UpdateManager.h"
#include "Enemy.h"
#include "Trap.h"
#include "Player.h"
#include "UIText.h"

void GameObjectManager::AddPlayer(sf::Vector2f const& position)
{
	player = std::make_shared<Player>(position, sf::Color::White);
	CollisionManager::GetInstance()->AddMovableGameObject(player);
	UpdateManager::GetInstance()->AddGameObject(player);
}

void GameObjectManager::AddEnemy(sf::Vector2f const& position)
{
	auto enemy{ std::make_shared<Enemy>(position, sf::Color::White) };
	enemies.push_back(enemy);
	CollisionManager::GetInstance()->AddMovableGameObject(enemy);
	UpdateManager::GetInstance()->AddGameObject(enemy);
}

void GameObjectManager::AddTrap(sf::Vector2f const& position)
{
	auto trap{ std::make_shared<Trap>(position, sf::Color::White) };
	traps.push_back(trap);
	CollisionManager::GetInstance()->AddStationaryGameObject(trap);
}

std::weak_ptr<UIText> GameObjectManager::AddUIText(sf::String const& text, sf::Vector2f const & screenPosition, sf::Color const & color, sf::RenderWindow const & window)
{
	auto uiText{ std::make_shared<UIText>(text, screenPosition, color, window) };
	texts.push_back(uiText);
	UpdateManager::GetInstance()->AddGameObject(uiText);

	return uiText;
}

void GameObjectManager::RemovePlayer()
{
	player = nullptr;
}

void GameObjectManager::RemoveEnemy(Enemy* enemy)
{
	for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		if (&*(*iter) == enemy)
		{
			enemies.erase(iter);
			return;
		}
	}
}

void GameObjectManager::RemoveText(UIText * text)
{
	for (auto iter = texts.begin(); iter != texts.end(); ++iter)
	{
		if (&*(*iter) == text)
		{
			texts.erase(iter);
			return;
		}
	}
}

std::weak_ptr<Player> GameObjectManager::GetPlayer() const
{
	return player;
}

bool GameObjectManager::IsPlayerAlive() const
{
	return player != nullptr && player->GetHitPoints() > 0;
}

bool GameObjectManager::AreEnemiesAlive() const
{
	return !enemies.empty();
}
