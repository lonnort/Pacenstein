#include "Definitions.hpp"
#include "SettingsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Pacenstein
{
	SettingsMenuState::SettingsMenuState(game_data_ref_t data) : data(data) { }

	void SettingsMenuState::init()
	{
        //Update to main menu background
		this->data->assets.loadTexture("Settings Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));
		//add sprites for title and back button
		this->data->assets.loadTexture("Settings Title", "res/ui/button.png");
		this->data->assets.loadTexture("Back Button", "res/ui/button.png");

		background.setTexture(this->data->assets.getTexture("Settings Menu Background"));
		title.setTexture(this->data->assets.getTexture("Settings Title"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		backButton.setPosition((backButton.getGlobalBounds().width / 2), (backButton.getGlobalBounds().height / 2));
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

			if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
			{
				std::cout << "Go To Previous Screen" << std::endl;
				this->data->machine.removeState();
			}
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
		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		this->data->window.display();
	}
}
