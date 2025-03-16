#include <assert.h>
#include "GameStateGameOver.h"
#include "Game.h"
#include "Application.h"
#include "Texts.h"

namespace Arcanoid
{
	void GameStateGameOverData::Init()
	{
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		MenuItem newGameItem;
		InitText(
			newGameItem.text,
			"Start new game",
			24,
			this->font);
		newGameItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().StartGame();
			};

		MenuItem mainMenuItem;
		InitText(
			mainMenuItem.text,
			"Exit main menu",
			24,
			this->font);
		mainMenuItem.text.setString("Exit main menu");
		mainMenuItem.text.setFont(this->font);
		mainMenuItem.text.setCharacterSize(24);
		mainMenuItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().Exit();
			};

		MenuItem gameOverMenu;
		InitText(
			gameOverMenu.hintText,
			"Game Over",
			24,
			this->font,
			sf::Color::Red);
		gameOverMenu.childrenOrientation = Orientation::Horizontal;
		gameOverMenu.childrenAlignment = Alignment::Middle;
		gameOverMenu.childrenSpacing = 20.f;
		gameOverMenu.childrens.push_back(newGameItem);
		gameOverMenu.childrens.push_back(mainMenuItem);

		this->menu.Init(gameOverMenu);
		
		int i = 0;
		auto recordsTable = ScoreManager::Instance()->GetShared()->GetRecordsTable();
		for (auto it = recordsTable.rbegin(); it != recordsTable.rend() && i < SETTINGS.NUM_RECORDS_IN_TABLE; it++, i++)
		{
			this->recordsTableTexts.emplace_back();
			sf::Text& text = this->recordsTableTexts.back();

			InitText(
				text,
				std::to_string(i + 1) + ". " + std::to_string(*it),
				24,
				this->font
			);
		}
		InitText(
			scoreText,
			"Your Score: " + std::to_string(ScoreManager::Instance()->GetShared()->GetScore()),
			24,
			this->font
		);
		this->background.setFillColor(sf::Color(0, 0, 0, 128));
	}
	void GameStateGameOverData::HandleWindowEvent(const sf::Event& event)
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
	void GameStateGameOverData::Update(float timeDelta)
	{
	}
	void GameStateGameOverData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &this->menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.5f, 0.5f }));
		scoreText.setPosition(viewSize.x / 2.f, 300.f);
		window.draw(scoreText);

		this->menu.Draw(window, sf::Vector2f(viewSize.x / 2.f, viewSize.y * 0.75), { 0.5f, 0.f });
	}
}