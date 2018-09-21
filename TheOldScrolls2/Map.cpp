// Game Logic Test - Daniel Bortfeld 2018
#include "Map.h"
#include "DrawManager.h"

Map::Map(float MapWidth, float MapHeight, float TileSize)
{
	auto drawManager{ DrawManager::GetInstance() };

	for (float x = 0; x < MapWidth; ++x)
	{
		for (float y = 0; y < MapHeight; ++y)
		{
			auto tile{ std::make_shared<sf::RectangleShape>() };

			tile->setSize({ TileSize - 1.f, TileSize - 1.f });
			tile->setPosition({ x*TileSize, y*TileSize });
			tile->setFillColor(sf::Color::Blue);

			tiles.push_back(tile);
			drawManager->AddDrawable(tile);
		}
	}
}