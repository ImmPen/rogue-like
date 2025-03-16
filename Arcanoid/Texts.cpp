#include "Texts.h"

namespace Arcanoid
{
	void InitText(sf::Text& text, std::string textString, int charSize, const sf::Font & font, const sf::Color & color)
	{
		text.setString(textString);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(charSize);
	}
	void InitText(sf::Text& text, std::string textString, int charSize, const sf::Font& font)
	{
		InitText(text, textString, charSize, font, sf::Color::White);
	}
}