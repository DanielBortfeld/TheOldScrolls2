// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef ENEMY_H
#define	ENEMY_H

#include "GameObject.h"
#include "SpriteAnimator.h"

class Player;

class Enemy : public GameObject
{
private:

	std::weak_ptr<Player> player;

	SpriteAnimator animator;

public:
	Enemy();
	Enemy(sf::Vector2f const& position, sf::Color const& color);
	virtual ~Enemy() = default;

	void Init();

	// Inherited via GameObject
	virtual void Update(sf::Time const& deltaTime) override;
	virtual void Die() override;
	virtual void OnCollisionEnter(std::shared_ptr<GameObject> const& other) override;
};

#endif // !ENEMY_H
