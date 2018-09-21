// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "UI.h"
#include "SpriteAnimator.h"

#include <SFML\System\Clock.hpp>

class GameObject;

class Player : public GameObject
{
private:

	int hitPoints;
	int score;

	sf::Vector2f targetLocation;
	bool isMoving;

	UI ui;

	bool isFlashing;
	sf::Clock flashingTimer;
	float flashingTimeSeconds;

	SpriteAnimator animator;

public:
	Player();
	Player(sf::Vector2f const& position, sf::Color const& color);
	virtual ~Player() = default;

	void Init();

	void SetTargetLocation(sf::Vector2f const& targetLocation);
	void SetIsMoving(bool isMoving);

	void ApplyDamage();
	void IncreaseScore();

	int GetHitPoints() const;
	int GetScore() const;

	sf::String GetHitPointsText() const;
	sf::String GetScoreText() const;

	void SetUIElements(UI const& ui);

	bool IsVulnerable() const;

	// Inherited via GameObject
	virtual void Update(sf::Time const& deltaTime) override;
	virtual void Die() override;

private:

	void UpdateUIElements();
};

#endif // !PLAYER_H
