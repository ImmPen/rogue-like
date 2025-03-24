#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "TransformComponent.h"
#include "GameObject.h"

namespace Engine
{
	class SpriteRendererComponent : public Component
	{
		SpriteRendererComponent(GameObject* gameObject);
		~SpriteRendererComponent();

		void Update(float timeDelta) override;
		void Render() override;

		const sf::Sprite* GetSprite() const;
		void SetTexture(const sf::Texture& newTexture);
		void SetPixelSize(int newWidth, int newHeight);

		void FlipX(bool flip);
		void FlipY(bool flip);

	private:
		sf::Sprite* sprite;
		TransformComponent* transform;

		bool isFlipX = false;
		bool isFlipY = false;
	};
}
