#include <assert.h>
#include "GameObject.h"
#include "Sprite.h"

namespace Arcanoid
{
	GameObject::GameObject(const std::string& texture, const sf::IntRect& rectInTexture, const sf::Vector2f& position, int desiredWidth, int desiredHeight)
		: startPosition(position)
	{
		assert(this->texture.loadFromFile(texture, rectInTexture));

		InitSprite(this->sprite, desiredWidth, desiredHeight, this->texture);
		this->sprite.setPosition(position);
	}
	void GameObject::Draw(sf::RenderWindow& window)
	{
		window.draw(this->sprite);
	}
	void GameObject::Restart()
	{
		this->sprite.setPosition(startPosition);
	}
}