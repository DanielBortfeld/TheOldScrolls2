// Game Logic Test - Daniel Bortfeld 2018
#include "Player.h"

#include "Constants.h"
#include "Util.h"
#include "GameObjectManager.h"
#include "GameObject.h"

#include <iostream>
#include <SFML\Graphics.hpp>

Player::Player()
	: GameObject()
	, isMoving(false)
	, animator("", 0, { 0, 0 }, { 0, 0 })
{
	Init();
}

Player::Player(sf::Vector2f const & position, sf::Color const & color)
	: GameObject(position, color)
	, isMoving(false)
	, animator("spriteSheet.png", 0.2f, { 35, 40 }, { 0, 0 })
{
	Init();
}

void Player::Init()
{
	Speed = TileSize * 3;
	hitPoints = 3;
	score = 0;
	isFlashing = false;
	flashingTimeSeconds = 3.f;

	shape->setTexture(animator.GetSpriteSheet());
}

void Player::SetTargetLocation(sf::Vector2f const & targetLocation)
{
	this->targetLocation = targetLocation;
}

void Player::SetIsMoving(bool isMoving)
{
	this->isMoving = isMoving;
}

void Player::ApplyDamage()
{
	if (isFlashing)
		return;

	--hitPoints;
	isFlashing = true;
	flashingTimer.restart();

	//std::cout << "hitPoints: " << hitPoints << "\n";

	UpdateUIElements();

	if (hitPoints <= 0)
	{
		Die();
	}
}

void Player::IncreaseScore()
{
	score += 100;

	//std::cout << "score: " << score << "\n";

	UpdateUIElements();
}

int Player::GetHitPoints() const
{
	return hitPoints;
}

int Player::GetScore() const
{
	return score;
}

sf::String Player::GetHitPointsText() const
{
	char buffer[16];
	sprintf_s<16>(buffer, "HP: %d", hitPoints);
	return buffer;
}

sf::String Player::GetScoreText() const
{
	char buffer[20];
	sprintf_s<20>(buffer, "Score: %d", score);
	return buffer;
}

void Player::SetUIElements(UI const& ui)
{
	this->ui = ui;
	UpdateUIElements();
}

bool Player::IsVulnerable() const
{
	return !isFlashing;
}

void Player::Update(sf::Time const& deltaTime)
{
	if (isMoving)
	{
		sf::Vector2f offset{ TileSize / 2, TileSize / 2 };

		auto pos{ GetPosition() + offset };
		pos.x /= TileSize;
		pos.y /= TileSize;

		auto dir{ targetLocation - pos };

		if (!(dir.x == 0 && dir.y == 0))
		{
			auto dirMag{ sqrtf(dir.x*dir.x + dir.y* dir.y) };

			dir.x = dir.x / dirMag;
			dir.y = dir.y / dirMag;

			Direction = dir;

			SetPosition(GetPosition() + Direction * Speed * deltaTime.asSeconds());
		}

		pos = GetPosition() + offset;

		if (Util::Distance({ pos.x / TileSize, pos.y / TileSize }, targetLocation) < 0.2f)
		{
			isMoving = false;
			Direction = { 0, 0 };
		}
	}

	if (isFlashing)
	{
		float elapsedSeconds{ flashingTimer.getElapsedTime().asSeconds() };
		if (elapsedSeconds > flashingTimeSeconds)
		{
			isFlashing = false;
			shape->setFillColor(sf::Color::White);
		}
		else
		{
			sf::Color color = sf::Color::White;
			color.a = 255 * (elapsedSeconds - static_cast<int>(elapsedSeconds));

			shape->setFillColor(color);
		}
	}

	animator.Update(Direction);
	shape->setTextureRect(animator.GetSpriteRect());
}

void Player::Die()
{
	GameObjectManager::GetInstance()->RemovePlayer();
}

void Player::UpdateUIElements()
{
	if (!ui.hitPointsText.expired())
	{
		ui.hitPointsText.lock()->SetText(GetHitPointsText());
	}

	if (!ui.scoreText.expired())
	{
		ui.scoreText.lock()->SetText(GetScoreText());
	}
}
