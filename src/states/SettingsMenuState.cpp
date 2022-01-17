#include "Definitions.hpp"
#include "SettingsMenuState.hpp"

#include <iostream>

namespace Pacenstein
{
	SettingsMenuState::SettingsMenuState(game_data_ref_t data) : data(data) { }

	void SettingsMenuState::init()
	{
        //Update to main menu background
		this->data->assets.loadTexture("Settings Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));
		//add sprites for title and start button
		//this->data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		//this->data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		background.setTexture(this->data->assets.getTexture("Settings Menu Background"));
		//title.setTexture(this->data->assets.GetTexture("Game Title"));
		//playButton.setTexture(this->data->assets.GetTexture("Play Button"));

		//title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		//playButton.setPosition((SCREEN_WIDTH / 2) - (playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (playButton.getGlobalBounds().height / 2));
	}

	void SettingsMenuState::handleInput()
	{
		sf::Event event;

		while (this->data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->data->window.close();
			}

			/*if (this->data->input.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
			{
				std::cout << "Go To Game Screen" << std::endl;
			}*/
		}
	}

	void SettingsMenuState::update(float dt)
	{
		std::cout << "In settings menu" << std::endl;
	}

	void SettingsMenuState::draw(float dt)
	{
		this->data->window.clear();
		this->background.setScale(20,20);
		this->data->window.draw(this->background);
		//this->data->window.draw(this->title);
		//this->data->window.draw(this->playButton);

		this->data->window.display();
	}
}
