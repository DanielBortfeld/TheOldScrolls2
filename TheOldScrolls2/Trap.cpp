// Game Logic Test - Daniel Bortfeld 2018
#include "Trap.h"

Trap::Trap() : GameObject()
{
}

Trap::Trap(sf::Vector2f const & position, sf::Color const & color)
	: GameObject(position, color)
{
}

void Trap::Update(sf::Time const& deltaTime)
{
}

void Trap::Die()
{
}
