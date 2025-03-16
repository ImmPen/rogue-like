#pragma once
#include "GameStateData.h"
#include "Menu.h"

namespace Arcanoid
{
    class GameStateWinData :
        public GameStateData
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

		Menu menu;
    };
}
