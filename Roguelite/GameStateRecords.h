#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.h"

namespace RogueLite
{
	class GameStateRecordsData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
}
