#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Arcanoid
{
	void InitText(sf::Text& text, std::string textString, int charSize, const sf::Font & font, const sf::Color & color);
	void InitText(sf::Text& text, std::string textString, int charSize, const sf::Font& font);
}
