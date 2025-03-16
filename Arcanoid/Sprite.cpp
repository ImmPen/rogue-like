#include "Sprite.h"

namespace Arcanoid
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		SetSpriteSize(sprite, desiredWidth, desiredHeight);
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void DrawSprite(sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
}