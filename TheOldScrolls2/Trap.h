// Game Logic Test - Daniel Bortfeld 2018
#pragma once
#ifndef TRAP_H
#define TRAP_H

#include "GameObject.h"

class Trap : public GameObject
{
public:
	Trap();
	Trap(sf::Vector2f const& position, sf::Color const& color);
	virtual ~Trap() = default;

	// Inherited via GameObject
	virtual void Update(sf::Time const& deltaTime) override;
	virtual void Die() override;
};

#endif // !TRAP_H
