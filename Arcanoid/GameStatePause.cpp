#include "GameStatePause.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStatePauseData::Init()
	{
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(this->font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().ExitAndSave();
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(this->font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().PopState();
			};

		MenuItem exitMenu;
		exitMenu.hintText.setString("Are you sure you want to stop this game?");
		exitMenu.hintText.setFont(this->font);
		exitMenu.hintText.setCharacterSize(24);
		exitMenu.hintText.setFillColor(sf::Color::Red);
		exitMenu.childrenOrientation = Orientation::Horizontal;
		exitMenu.childrenAlignment = Alignment::Middle;
		exitMenu.childrenSpacing = 20.f;
		exitMenu.childrens.push_back(yesItem);
		exitMenu.childrens.push_back(noItem);

		this->menu.Init(exitMenu);

		this->background.setFillColor(sf::Color(0, 0, 0, 128));
	}

	void GameStatePauseData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				this->menu.PressOnSelectedItem();
			}

			Orientation orientation = this->menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SoundManager::Instance().PlaySound(Sounds::menuHoverSound);
				this->menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SoundManager::Instance().PlaySound(Sounds::menuHoverSound);
				this->menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStatePauseData::Update(float timeDelta)
	{
	}

	void GameStatePauseData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		this->background.setSize(viewSize);
		window.draw(this->background);

		sf::Text* hintText = &this->menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		this->menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}