// Game Logic Test - Daniel Bortfeld 2018
#include "UIText.h"

#include "Constants.h"
#include "DrawManager.h"

#include <SFML\Graphics.hpp>
#include <iostream>

UIText::UIText(sf::RenderWindow const& window)
	: UIText("TEXT", { 0.f, 0.f }, sf::Color::White, window)
{
}

UIText::UIText(sf::String const& text, sf::Vector2f const & screenPosition, sf::Color const & color, sf::RenderWindow const& window)
	: window(window)
	, screenPosition(screenPosition)
{
	this->font = std::make_shared<sf::Font>();
	//std::cout << "font loaded:" << font->loadFromFile("Planewalker.otf") << "\n";
	font->loadFromFile("Planewalker.otf");

	this->text = std::make_shared<sf::Text>();
	this->text->setFont(*font);
	this->text->setString(text);
	this->text->setFillColor(color);
	this->text->setCharacterSize(50);

	DrawManager::GetInstance()->AddDrawable(this->text);
}

void UIText::SetText(sf::String const& text)
{
	if (this->text != nullptr)
	{
		this->text->setString(text);
	}
}

void UIText::Update(sf::Time const& deltaTime)
{
	auto screenOffset{ window.getView().getCenter() - sf::Vector2f{ ScreenWidth / 2, ScreenHeight / 2 } };

	text->setPosition(screenPosition + screenOffset);
}

void UIText::Die()
{
}
