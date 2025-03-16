#include "GameStateRecords.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"
#include "Menu.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStateRecordsData::Init()
	{
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		this->titleText.setString("Records");
		this->titleText.setFont(this->font);
		this->titleText.setFillColor(sf::Color::Red);
		this->titleText.setCharacterSize(48);

		this->tableTexts.reserve(SETTINGS.NUM_RECORDS_IN_TABLE);

		int i = 0;
		auto recordsTable = ScoreManager::Instance()->GetShared()->GetRecordsTable();
		for (auto it = recordsTable.rbegin(); it != recordsTable.rend() && i < SETTINGS.NUM_RECORDS_IN_TABLE; it++, i++)
		{
			this->tableTexts.emplace_back();
			sf::Text& text = this->tableTexts.back();

			text.setString(std::to_string(i + 1) + ". " + std::to_string(*it));
			text.setFont(this->font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		this->hintText.setString("Press ESC to return to main menu");
		this->hintText.setFont(this->font);
		this->hintText.setFillColor(sf::Color::White);
		this->hintText.setCharacterSize(24);
	}
	void GameStateRecordsData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().Exit();
			}
		}
	}
	void GameStateRecordsData::Update(float timeDelta)
	{

	}
	void GameStateRecordsData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		this->titleText.setOrigin(GetTextOrigin(this->titleText, { 0.5f, 0.f }));
		this->titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(this->titleText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(this->tableTexts.size());
		for (auto& text : this->tableTexts)
		{
			textsList.push_back(&text);
		}
		sf::Vector2f tablePosition = { viewSize.x / 2.f, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.5f });

		this->hintText.setOrigin(GetTextOrigin(this->hintText, { 0.5f, 1.f }));
		this->hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(this->hintText);
	}
}
