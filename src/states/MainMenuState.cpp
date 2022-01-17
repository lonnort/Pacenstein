#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "InGameState.hpp"
#include "LeaderboardMenuState.hpp"
#include "SettingsMenuState.hpp"
#include "CreditsMenuState.hpp"

#include <iostream>

namespace Pacenstein
{
	MainMenuState::MainMenuState(game_data_ref_t data) : data(data) { }

	void MainMenuState::init()
	{
        //Update to main menu background
		// this->data->assets.loadTexture("Main Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));
		// add sprites for title and start button
		this->data->assets.loadTexture("Game Title", "res/pacenstein.png");
		this->data->assets.loadTexture("Start Game Button", (BUTTONS_FILEPATH "start_game.png"));
		this->data->assets.loadTexture("Leaderboard Button", (BUTTONS_FILEPATH "leaderboard.png"));
		this->data->assets.loadTexture("Settings Button", (BUTTONS_FILEPATH "settings.png"));
		this->data->assets.loadTexture("Quit Game Button", (BUTTONS_FILEPATH "quit_game.png"));
		this->data->assets.loadTexture("Credits Button", (BUTTONS_FILEPATH "question.png"));

		// background.setTexture(this->data->assets.getTexture("Main Menu Background"));
		title.setTexture(this->data->assets.getTexture("Game Title"));
		StartButton.setTexture(this->data->assets.getTexture("Start Game Button"));
		LeaderboardButton.setTexture(this->data->assets.getTexture("Leaderboard Button"));
		SettingsButton.setTexture(this->data->assets.getTexture("Settings Button"));
		QuitButton.setTexture(this->data->assets.getTexture("Quit Game Button"));
		CreditsButton.setTexture(this->data->assets.getTexture("Credits Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2 * 0.3), title.getGlobalBounds().height / 2 * 0.3);
		StartButton.setPosition((SCREEN_WIDTH / 2) - (StartButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (StartButton.getGlobalBounds().height / 2));
		LeaderboardButton.setPosition((SCREEN_WIDTH / 2) - (LeaderboardButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (LeaderboardButton.getGlobalBounds().height / 2) + 75);
		SettingsButton.setPosition((SCREEN_WIDTH / 2) - (SettingsButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (SettingsButton.getGlobalBounds().height / 2) + 150);
		QuitButton.setPosition((SCREEN_WIDTH / 2) - (QuitButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (QuitButton.getGlobalBounds().height / 2) + 225);
		CreditsButton.setPosition(100, (SCREEN_HEIGHT - 100) - (CreditsButton.getGlobalBounds().height));
	}

	void MainMenuState::handleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type){
				this->data->window.close();
			}

			if (this->data->input.isSpriteClicked(this->StartButton, sf::Mouse::KEY_ALT_LEFT, this->data->window)){
				this->data->machine.addState(state_ref_t(std::make_unique<InGameState>(this->data)), false);
			}
			if (this->data->input.isSpriteClicked(this->LeaderboardButton, sf::Mouse::KEY_ALT_LEFT, this->data->window)){
				this->data->machine.addState(state_ref_t(std::make_unique<LeaderboardMenuState>(this->data)), false);
			}
			if (this->data->input.isSpriteClicked(this->SettingsButton, sf::Mouse::KEY_ALT_LEFT, this->data->window)){
				this->data->machine.addState(state_ref_t(std::make_unique<SettingsMenuState>(this->data)), false);
			}
			if (this->data->input.isSpriteClicked(this->QuitButton, sf::Mouse::KEY_ALT_LEFT, this->data->window)){
				this->data->window.close();
			}
			if (this->data->input.isSpriteClicked(this->CreditsButton, sf::Mouse::KEY_ALT_LEFT, this->data->window)){
				this->data->machine.addState(state_ref_t(std::make_unique<CreditsMenuState>(this->data)), false);
			}
		}
	}

	void MainMenuState::update(float dt)
	{
		std::cout << "In main menu" << std::endl;
	}

	void MainMenuState::draw(float dt)
	{
		this->data->window.clear();
		this->title.setScale(0.3,0.3);
		// this->data->window.draw(this->background);

		this->data->window.draw(this->title);
		this->data->window.draw(this->StartButton);
		this->data->window.draw(this->LeaderboardButton);
		this->data->window.draw(this->SettingsButton);
		this->data->window.draw(this->QuitButton);
		this->data->window.draw(this->CreditsButton);

		this->data->window.display();
	}
}
