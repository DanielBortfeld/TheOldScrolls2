// Game Logic Test - Daniel Bortfeld 2018
#include "SpriteAnimator.h"

#include <iostream>

SpriteAnimator::SpriteAnimator(sf::String const& filename, float frameDelaySeconds, sf::Vector2i const& spriteSize, sf::Vector2i const& startPoint)
	: frameDelaySeconds(frameDelaySeconds)
	, spriteSize(spriteSize)
	, currentSubRect{ 0, Down }

{
	spriteSheet = std::make_unique<sf::Texture>();

	//std::cout << "spriteSheet loaded:" << LoadSpriteSheet(filename, spriteSize, startPoint) << "\n";
	LoadSpriteSheet(filename, spriteSize, startPoint);
}

void SpriteAnimator::Update(sf::Vector2f direction)
{
	if (delayTimer.getElapsedTime().asSeconds() >= frameDelaySeconds)
	{
		delayTimer.restart();


		if (direction.x == 0 && direction.y == 0)
		{
			currentSubRect.spriteNumber = 0;
		}
		else
		{
			if (direction.x * 1 + direction.y * 1 > 0)
			{
				if (direction.x * -1 + direction.y * 1 > 0)
				{
					currentSubRect.direction = Down;
				}
				else
				{
					currentSubRect.direction = Right;
				}
			}
			else
			{
				if (direction.x * 1 + direction.y * -1 > 0)
				{
					currentSubRect.direction = Up;
				}
				else
				{
					currentSubRect.direction = Left;
				}
			}

			currentSubRect.spriteNumber++;

			if (currentSubRect.spriteNumber >= spritesPerAnim)
			{
				currentSubRect.spriteNumber = 0;
			}
		}
	}
}

bool SpriteAnimator::LoadSpriteSheet(sf::String const & filename, sf::Vector2i spriteSize, sf::Vector2i const& startPoint)
{
	bool returnValue = spriteSheet->loadFromFile(filename);

	for (int i = Down; i < DIRECTION_MAX; ++i)
	{
		for (int j = 0; j < spritesPerAnim; ++j)
		{
			allRects[j][i] = {
				startPoint.x + j * spriteSize.x,
				startPoint.y + i * spriteSize.y,
				spriteSize.x,
				spriteSize.y
			};
		}
	}

	return returnValue;
}

sf::IntRect SpriteAnimator::GetSpriteRect() const
{
	return allRects[currentSubRect.spriteNumber][currentSubRect.direction];
}

sf::RectangleShape SpriteAnimator::GetCurrentSprite()
{
	currentSprite.setTexture(spriteSheet.get());
	currentSprite.setTextureRect(GetSpriteRect());
	return currentSprite;
}

const sf::Texture * SpriteAnimator::GetSpriteSheet() const
{
	return spriteSheet.get();
}
