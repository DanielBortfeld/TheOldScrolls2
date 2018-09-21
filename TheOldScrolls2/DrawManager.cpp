// Game Logic Test - Daniel Bortfeld 2018
#include "DrawManager.h"

#include <SFML\Graphics.hpp>

void DrawManager::DrawAllDrawables(sf::RenderWindow& window) const
{
	for (auto& drawable : drawables)
	{
		if (!drawable.expired())
		{
			window.draw(*(drawable.lock()));
		}
	}
}


void DrawManager::AddDrawable(std::weak_ptr<sf::Drawable> const& drawable)
{
	if (!drawable.expired())
	{
		drawables.push_back(drawable);
	}
}
