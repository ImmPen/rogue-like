#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameStateData.h"

namespace Arcanoid
{
	class GameStateGameOverData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;

		sf::RectangleShape background;

		std::vector<sf::Text> recordsTableTexts;
		sf::Text scoreText;

		Menu menu;
	};
}