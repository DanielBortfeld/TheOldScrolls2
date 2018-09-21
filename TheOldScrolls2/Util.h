// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <SFML\System\Vector2.hpp>
#include <SFML\System\Clock.hpp>

class Util
{
public:

	static sf::Time DeltaTime;

public:
	Util() = delete;

	static float DistanceFromPixelInTiles(sf::Vector2f const& StartInPx, sf::Vector2f const& TargetInPx);
	static float Distance(sf::Vector2f const& StartInPx, sf::Vector2f const& TargetInPx);
};

#endif // !UTIL_H
