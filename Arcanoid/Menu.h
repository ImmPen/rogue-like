#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace Arcanoid
{
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; // Visible when child item is selected
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		std::vector<MenuItem> childrens;
		
		std::function<void(MenuItem& item)> onPressCallback;

		MenuItem* parent = nullptr;
	};

	class Menu
	{
	public:
		void Init(const MenuItem& item);

		void Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);

		void PressOnSelectedItem();	// press on selected menu item
		void GoBack();	// go back to previous menu

		void SwitchToPreviousMenuItem();
		void SwitchToNextMenuItem();

		MenuItem& GetCurrentContext();
	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;

		void InitMenuItem(MenuItem& item);
		void SelectMenuItem(MenuItem& item);
	};

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
}
