// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\System\Time.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <memory>

class GameObject
{
public:

	float Speed{ 0.f };
	sf::Vector2f Direction{ 0.f, 0.f };

protected:

	std::shared_ptr<sf::RectangleShape> shape;

public:
	GameObject();
	GameObject(sf::Vector2f const& position, sf::Color const& color);
	virtual ~GameObject() = default;

	void SetPosition(sf::Vector2f const& newPosition);
	sf::Vector2f GetPosition() const;

	void SetColor(sf::Color const& newColor);
	sf::Color GetColor() const;

	sf::FloatRect GetBounds() const;

	virtual void Update(sf::Time const& deltaTime) = 0;
	virtual void OnCollisionEnter(std::shared_ptr<GameObject> const& other);
	virtual void Die() = 0;
};

#endif // !GAMEOBJECT_H
