#include "GameStateMainMenu.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStateMainMenuData::Init()
	{
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(this->font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().StartGame();
			};

		/*MenuItem continueGame;
		continueGame.text.setString("Continue Game");
		continueGame.text.setFont(this->font);
		continueGame.text.setCharacterSize(24);
		continueGame.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().LoadSaves();
			};
		*/
		const bool isMusicOn = Application::Instance().GetGame().IsEnableOptions(GameOptions::MUSIC_ON);
		MenuItem optionsMusicOn;
		optionsMusicOn.text.setString("Music on: " + std::string(isMusicOn ? "On" : "Off"));
		optionsMusicOn.text.setFont(this->font);
		optionsMusicOn.text.setCharacterSize(24);
		optionsMusicOn.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			bool newOptionValue = !game.IsEnableOptions(GameOptions::MUSIC_ON);
			game.SetOption(GameOptions::MUSIC_ON, newOptionValue);
			item.text.setString("Music on: " + std::string(newOptionValue ? "On" : "Off"));
			};

		const bool isSoundsOn = Application::Instance().GetGame().IsEnableOptions(GameOptions::SOUNDS_ON);
		MenuItem optionsSoundsOn;
		optionsSoundsOn.text.setString("Sounds on: " + std::string(isSoundsOn ? "On" : "Off"));
		optionsSoundsOn.text.setFont(this->font);
		optionsSoundsOn.text.setCharacterSize(24);
		optionsSoundsOn.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			bool newOptionValue = !game.IsEnableOptions(GameOptions::SOUNDS_ON);
			game.SetOption(GameOptions::SOUNDS_ON, newOptionValue);
			item.text.setString("Sounds on: " + std::string(newOptionValue ? "On" : "Off"));
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(this->font);
		options.text.setCharacterSize(24);
		options.hintText.setString("Options");
		options.hintText.setFont(this->font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsMusicOn);
		options.childrens.push_back(optionsSoundsOn);

		MenuItem recordsItem;
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(this->font);
		recordsItem.text.setCharacterSize(24);
		recordsItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().ShowRecords();
			};

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(this->font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().QuitGame();
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(this->font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [this](MenuItem&) {
			this->menu.GoBack();
			};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(this->font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(this->font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		mainMenu.hintText.setString("Snake Game");
		mainMenu.hintText.setFont(this->font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		//mainMenu.childrens.push_back(continueGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(exitGameItem);


		this->menu.Init(mainMenu);
	}

	void GameStateMainMenuData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->menu.GoBack();
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

	void GameStateMainMenuData::Update(float timeDelta)
	{
	}

	void GameStateMainMenuData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &this->menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		this->menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
