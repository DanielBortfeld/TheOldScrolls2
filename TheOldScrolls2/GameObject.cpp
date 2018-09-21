// Game Logic Test - Daniel Bortfeld 2018
#include "GameObject.h"

#include "Constants.h"
#include "Util.h"
#include "DrawManager.h"
#include "UpdateManager.h"

#include <SFML\Graphics.hpp>

GameObject::GameObject()
{
	shape = std::make_shared<sf::RectangleShape>();
	shape->setSize({ static_cast<float>(TileSize), static_cast<float>(TileSize) });

	DrawManager::GetInstance()->AddDrawable(shape);
}

GameObject::GameObject(sf::Vector2f const & position, sf::Color const & color)
	: GameObject()
{
	shape->setPosition(position);
	shape->setFillColor(color);
}

void GameObject::SetPosition(sf::Vector2f const & newPosition)
{
	shape->setPosition(newPosition);
}

sf::Vector2f GameObject::GetPosition() const
{
	return shape->getPosition();
}

void GameObject::SetColor(sf::Color const & newColor)
{
	shape->setFillColor(newColor);
}

sf::Color GameObject::GetColor() const
{
	return shape->getFillColor();
}

sf::FloatRect GameObject::GetBounds() const
{
	sf::FloatRect bounds{ shape->getLocalBounds() };
	sf::Vector2f position{ GetPosition() };

	return { position.x, position.y, bounds.width, bounds.height };
}

void GameObject::OnCollisionEnter(std::shared_ptr<GameObject> const& other)
{
	SetPosition(GetPosition() - Direction * Speed * Util::DeltaTime.asSeconds());
}

