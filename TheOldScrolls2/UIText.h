// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "GameObject.h"
#include <memory>
#include <SFML\Graphics.hpp>

class UIText : public GameObject
{
private:

	std::shared_ptr<sf::Font> font;
	std::shared_ptr<sf::Text> text;
	sf::RenderWindow const& window;
	sf::Vector2f const& screenPosition;

public:
	UIText(sf::RenderWindow const& window);
	UIText(sf::String const& text, sf::Vector2f const& screenPosition, sf::Color const& color, sf::RenderWindow const& window);
	~UIText() = default;

	void SetText(sf::String const& text);

	// Inherited via GameObject
	virtual void Update(sf::Time const& deltaTime) override;
	virtual void Die() override;
};

#endif // !UI_TEXT_H
