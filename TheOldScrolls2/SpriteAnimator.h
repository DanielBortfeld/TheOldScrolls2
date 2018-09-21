// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include <SFML\Graphics.hpp>
#include <memory>

class SpriteAnimator
{
public:

	enum Direction
	{
		Down,
		Left,
		Right,
		Up,

		DIRECTION_MAX
	};

private:

	struct SpriteCoordinates
	{
		int spriteNumber;
		Direction direction;
	};

private:

	static const int spritesPerAnim = 3;

	std::unique_ptr<sf::Texture> spriteSheet;
	sf::RectangleShape currentSprite;
	sf::IntRect allRects[spritesPerAnim][DIRECTION_MAX];
	SpriteCoordinates currentSubRect;
	sf::Vector2i spriteSize;

	sf::Clock delayTimer;
	float frameDelaySeconds;

public:
	SpriteAnimator(sf::String const& filename, float frameDelaySeconds, sf::Vector2i const& spriteSize, sf::Vector2i const& startPoint);
	~SpriteAnimator() = default;

	void Update(sf::Vector2f direction);

	bool LoadSpriteSheet(sf::String const& filename, sf::Vector2i spriteSize, sf::Vector2i const& startPoint);

	sf::IntRect GetSpriteRect() const;
	sf::RectangleShape GetCurrentSprite();
	const sf::Texture* GetSpriteSheet() const;
};

#endif // !SPRITE_ANIMATOR_H
