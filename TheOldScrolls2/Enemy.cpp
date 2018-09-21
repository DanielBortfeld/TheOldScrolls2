// Game Logic Test - Daniel Bortfeld 2018
#include "Enemy.h"
#include "Constants.h"
#include "Trap.h"
#include "GameObjectManager.h"
#include "Player.h"

#include <SFML\System.hpp>

Enemy::Enemy() 
	: GameObject()
	, animator("", 0, { 0, 0 }, { 0, 0 })
{
	Init();
}

Enemy::Enemy(sf::Vector2f const & position, sf::Color const & color)
	: GameObject(position, color)	
	, player(GameObjectManager::GetInstance()->GetPlayer())
	, animator("spriteSheet.png", 0.2f, { 35, 40 }, { 0, 160 })

{
	Init();
}

void Enemy::Init()
{
	Speed = TileSize * 2;
	shape->setTexture(animator.GetSpriteSheet());
}

void Enemy::Update(sf::Time const& deltaTime)
{
	if (player.expired())
	{
		player = GameObjectManager::GetInstance()->GetPlayer();

		if (player.expired())
			return;
	}

	sf::Vector2f centerPosition{ GetPosition() + sf::Vector2f(TileSize / 2, TileSize / 2) };
	sf::Vector2f playerCenterPosition{ player.lock()->GetPosition() + sf::Vector2f(TileSize / 2, TileSize / 2) };

	sf::Vector2f vectorToPlayer{ playerCenterPosition - centerPosition };

	float squaredDistanceToPlayer{ vectorToPlayer.x * vectorToPlayer.x + vectorToPlayer.y * vectorToPlayer.y };

	if (squaredDistanceToPlayer < EnemyChaseRange*EnemyChaseRange)
	{
		centerPosition.x /= TileSize;
		centerPosition.y /= TileSize;

		sf::Vector2f dir{ vectorToPlayer };

		if (!(dir.x == 0 && dir.y == 0))
		{
			auto dirMag{ sqrtf(dir.x * dir.x + dir.y * dir.y) };

			dir.x = dir.x / dirMag;
			dir.y = dir.y / dirMag;

			Direction = dir;

			SetPosition(GetPosition() + Direction * Speed * deltaTime.asSeconds());
		}
	}
	else
	{
		Direction = { 0, 0 };
	}

	animator.Update(Direction);
	shape->setTextureRect(animator.GetSpriteRect());
}

void Enemy::Die()
{
	GameObjectManager::GetInstance()->RemoveEnemy(this);
}

void Enemy::OnCollisionEnter(std::shared_ptr<GameObject> const& other)
{
	GameObject::OnCollisionEnter(other);

	if (!player.expired())
	{
		auto playerPtr = player.lock();
		if (other == playerPtr)
		{
			if (playerPtr->IsVulnerable())
			{
				playerPtr->ApplyDamage();
				Die();
			}
		}
		else if (dynamic_cast<Trap*>(&*other))
		{
			playerPtr->IncreaseScore();
			Die();
		}
	}
}
