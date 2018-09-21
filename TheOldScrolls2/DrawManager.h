// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "Singleton.h"

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <memory>
#include <vector>

class DrawManager : public Singleton<DrawManager>
{
private:

	std::vector<std::weak_ptr<sf::Drawable>> drawables;

public:

	DrawManager() = default;
	~DrawManager() = default;

	void DrawAllDrawables(sf::RenderWindow& window) const;
	void AddDrawable(std::weak_ptr<sf::Drawable> const& drawable);
};

#endif // !DRAW_MANAGER_H
