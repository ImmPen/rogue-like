#include "Menu.h"
#include <assert.h>

namespace Arcanoid
{
	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetTextOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}
		}
	}
	
	void Menu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.childrens)
		{
			child.parent = &item;
			InitMenuItem(child);
		}
	}

	void Menu::SelectMenuItem(MenuItem& item)
	{
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->deselectedColor);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->selectedColor);
		}
	}

	void Menu::Init(const MenuItem& item)
	{
		rootItem = item;

		InitMenuItem(rootItem);
		if (!rootItem.childrens.empty()) {
			SelectMenuItem(rootItem.childrens.front());
		}
	}

	void Menu::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem& expandedItem = GetCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.childrens.size());
		for (auto& child : expandedItem.childrens) {
			texts.push_back(&child.text);
		}

		DrawTextList(
			window,
			texts,
			expandedItem.childrenSpacing,
			expandedItem.childrenOrientation,
			expandedItem.childrenAlignment,
			position,
			origin);
	}

	void Menu::PressOnSelectedItem()
	{
		if (!selectedItem) {
			return;
		}

		if (selectedItem->onPressCallback) {
			selectedItem->onPressCallback(*selectedItem);
			return;
		}

		// default behaviour
		if (!selectedItem->childrens.empty()) {
			SelectMenuItem(selectedItem->childrens.front());
		}
	}

	void Menu::GoBack()
	{
		MenuItem& parent = GetCurrentContext();
		if (&parent != &rootItem) {
			SelectMenuItem(parent);
		}
	}

	void Menu::SwitchToPreviousMenuItem()
	{
		if (!selectedItem) {
			return;
		}

		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(
			parent->childrens.begin(),
			parent->childrens.end(),
			[this](const auto& item) { return selectedItem == &item; });
		if (it != parent->childrens.begin()) {
			SelectMenuItem(*std::prev(it));
		}
	}

	void Menu::SwitchToNextMenuItem()
	{
		if (!selectedItem) {
			return;
		}

		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(
			parent->childrens.begin(),
			parent->childrens.end(),
			[this](const auto& item) { return selectedItem == &item; });
		it = std::next(it);
		if (it != parent->childrens.end()) {
			SelectMenuItem(*it);
		}
	}

	MenuItem& Menu::GetCurrentContext()
	{
		return selectedItem ? *(selectedItem->parent) : rootItem;
	}

}