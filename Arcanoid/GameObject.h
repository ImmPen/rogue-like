#pragma once
#include <SFML/Graphics.hpp>
namespace Arcanoid
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		GameObject(const std::string& texture, const sf::IntRect& rectInTexture, const sf::Vector2f& position, int desiredWidth, int desiredHeight);
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

		const sf::Vector2f& GetPosition() const { return this->sprite.getPosition(); }
		const sf::FloatRect& GetSpriteRect() const { return this->sprite.getGlobalBounds(); }
		virtual void Restart();
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
		const sf::Vector2f startPosition;
	};
}
