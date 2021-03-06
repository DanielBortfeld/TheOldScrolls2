// Game Logic Test - Daniel Bortfeld 2018
// TheOldScrolls2.cpp : Defines the entry point for the console application.
//

#include "DrawManager.h"
#include "Map.h"
#include "Player.h"
#include "Trap.h"
#include "Constants.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Util.h"
#include "GameObjectManager.h"
#include "UpdateManager.h"

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

void UpdateViewport(sf::RenderWindow& window)
{
	auto player{ GameObjectManager::GetInstance()->GetPlayer() };

	if (!player.expired())
	{
		auto playerPtr{ player.lock() };

		float viewportX;

		int playerX = playerPtr->GetPosition().x + TileSize / 2;
		int screenCenterX = ScreenWidth / 2;
		int rightBorder = TileSize * MapWidth;
		if (playerX < screenCenterX)
		{
			viewportX = screenCenterX;
		}
		else if (playerX > rightBorder - screenCenterX)
		{
			viewportX = rightBorder - screenCenterX;
		}
		else
		{
			viewportX = playerX;
		}

		float viewportY;

		int playerY = playerPtr->GetPosition().y + TileSize / 2;
		int screenCenterY = ScreenHeight / 2;
		int bottomBorder = TileSize * MapHeight;
		if (playerY < screenCenterY)
		{
			viewportY = screenCenterY;
		}
		else if (playerY > bottomBorder - screenCenterY)
		{
			viewportY = bottomBorder - screenCenterY;
		}
		else
		{
			viewportY = playerY;
		}

		window.setView(sf::View({ viewportX, viewportY }, window.getView().getSize()));
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Game Logic Test - Daniel Bortfeld", sf::Style::Titlebar | sf::Style::Close);

	auto drawManager{ DrawManager::GetInstance() };
	auto collisionManager{ CollisionManager::GetInstance() };
	auto updateManager{ UpdateManager::GetInstance() };
	auto gameObjectManager{ GameObjectManager::GetInstance() };

	//map
	Map map(MapWidth, MapHeight, TileSize);

	//traps
	std::vector<std::shared_ptr<Trap>> traps;
	for (int x = 0; x < MapWidth - 1; x += 4)
	{
		for (int y = 0; y < MapHeight - 1; y += 4)
		{
			gameObjectManager->AddTrap({ static_cast<float>(x * TileSize), static_cast<float>(y * TileSize) });
		}
	}

	//player
	gameObjectManager->AddPlayer({ static_cast<float>(TileSize), static_cast<float>(TileSize) });
	auto player{ gameObjectManager->GetPlayer() };

	// enemies
	std::vector<std::shared_ptr<Enemy>> enemies;
	for (int x = 22; x <= 26; x += 4)
	{
		for (int y = 10; y <= 22; y += 4)
		{
			gameObjectManager->AddEnemy({ static_cast<float>(x * TileSize), static_cast<float>(y * TileSize) });
		}
	}

	//texts

	auto hitPointsText{ gameObjectManager->AddUIText("HitPoints", { 10.f, 610.f }, sf::Color::Black, window) };
	auto scoreText{ gameObjectManager->AddUIText("Score", { 10.f, 650.f }, sf::Color::Black, window) };

	player.lock()->SetUIElements({ hitPointsText, scoreText });

	bool isLeftMouseButtonDown = false;
	sf::Vector2f mousePosition;
	bool gameOver = false;

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		Util::DeltaTime = deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePosition = { static_cast<float>(event.mouseButton.x) , static_cast<float>(event.mouseButton.y) };

				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					isLeftMouseButtonDown = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				mousePosition = { static_cast<float>(event.mouseButton.x) , static_cast<float>(event.mouseButton.y) };

				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					isLeftMouseButtonDown = false;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				mousePosition = { static_cast<float>(event.mouseMove.x) , static_cast<float>(event.mouseMove.y) };
			}
		}

		// move player
		if (!player.expired() && isLeftMouseButtonDown)
		{
			auto playerPtr{ player.lock() };

			auto screenOffset{ window.getView().getCenter() - sf::Vector2f{ ScreenWidth / 2, ScreenHeight / 2 } };

			auto mousePos{ sf::Vector2f{ (mousePosition.x + screenOffset.x) / TileSize, (mousePosition.y + screenOffset.y) / TileSize } };

			playerPtr->SetTargetLocation(mousePos);
			playerPtr->SetIsMoving(true);
		}
		// ~ move player

		updateManager->UpdateAllGameObjects(Util::DeltaTime);
		collisionManager->CheckCollisions();

		UpdateViewport(window);

		if (!gameOver)
		{
			if (!gameObjectManager->IsPlayerAlive())
			{
				auto youDiedText{ gameObjectManager->AddUIText("YOU DIED", { ScreenWidth / 2.f - 150.f, ScreenHeight / 2.f - 50.f }, sf::Color::Red, window) };
				gameOver = true;
			}
			else if (!gameObjectManager->AreEnemiesAlive())
			{
				auto youWonText{ gameObjectManager->AddUIText("YOU WON", { ScreenWidth / 2.f - 150.f, ScreenHeight / 2.f - 50.f }, sf::Color::Green, window) };
				gameOver = true;
			}
		}

		window.clear();
		drawManager->DrawAllDrawables(window);
		window.display();
	}

	return 0;
}

