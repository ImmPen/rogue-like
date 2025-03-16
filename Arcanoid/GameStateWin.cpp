#include "GameStateWin.h"
#include <assert.h>
#include "GameSettings.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStateWinData::Init()
	{
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		MenuItem newGameItem;
		newGameItem.text.setString("Start new game");
		newGameItem.text.setFont(this->font);
		newGameItem.text.setCharacterSize(24);
		newGameItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().StartGame();
			};

		MenuItem mainMenuItem;
		mainMenuItem.text.setString("Exit main menu");
		mainMenuItem.text.setFont(this->font);
		mainMenuItem.text.setCharacterSize(24);
		mainMenuItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().Exit();
			};

		MenuItem gameWinMenu;
		gameWinMenu.hintText.setString("Winner");
		gameWinMenu.hintText.setFont(this->font);
		gameWinMenu.hintText.setCharacterSize(24);
		gameWinMenu.hintText.setFillColor(sf::Color::Red);
		gameWinMenu.childrenOrientation = Orientation::Horizontal;
		gameWinMenu.childrenAlignment = Alignment::Middle;
		gameWinMenu.childrenSpacing = 20.f;
		gameWinMenu.childrens.push_back(newGameItem);
		gameWinMenu.childrens.push_back(mainMenuItem);

		this->menu.Init(gameWinMenu);

		int i = 0;
		auto recordsTable = ScoreManager::Instance()->GetShared()->GetRecordsTable();
		for (auto it = recordsTable.rbegin(); it != recordsTable.rend() && i < SETTINGS.NUM_RECORDS_IN_TABLE; it++, i++)
		{
			this->recordsTableTexts.emplace_back();
			sf::Text& text = this->recordsTableTexts.back();

			text.setString(std::to_string(i + 1) + ". " + std::to_string(*it));
			text.setFont(this->font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		this->background.setFillColor(sf::Color(0, 0, 0, 128));
	}
	void GameStateWinData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().Exit();
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
	void GameStateWinData::Update(float timeDelta)
	{
	}
	void GameStateWinData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &this->menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		this->menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}