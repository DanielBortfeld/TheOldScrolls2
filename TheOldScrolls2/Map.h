// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics\RectangleShape.hpp>
#include <vector>
#include <memory>

class Map
{
private:

	std::vector<std::shared_ptr<sf::RectangleShape>> tiles;
	
public:
	Map(float MapWidth, float MapHeight, float TileSize);
	~Map() = default;
};

#endif // !MAP_H
