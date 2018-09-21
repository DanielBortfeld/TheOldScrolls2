// Game Logic Test - Daniel Bortfeld 2018
#include "Util.h"
#include "Constants.h"
#include <math.h>

sf::Time Util::DeltaTime;

float Util::DistanceFromPixelInTiles(sf::Vector2f const & A, sf::Vector2f const & B)
{
	float aX = A.x / TileSize;
	float aY = A.y / TileSize;
	float bX = B.x / TileSize;
	float bY = B.y / TileSize;

	float dX = bX - aX;
	float dY = bY - aY;

	return sqrtf(dX * dX + dY * dY);
}

float Util::Distance(sf::Vector2f const & A, sf::Vector2f const & B)
{
	float dX = B.x - A.x;
	float dY = B.y - A.y;

	return sqrtf(dX * dX + dY * dY);
}
