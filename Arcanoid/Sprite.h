#pragma once
#include <SFML/Graphics.hpp>

namespace Arcanoid
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void DrawSprite(sf::Sprite& sprite, sf::RenderWindow& window);
}

