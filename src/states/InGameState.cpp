#include <sstream>
#include "Definitions.hpp"
#include "InGameState.hpp"

#include <iostream>

namespace Pacenstein
{
	InGameState::InGameState(game_data_ref_t data) : data(data) { }

	void InGameState::init()
	{
                //Update to main menu background
		this->data->assets.loadTexture("In Game Background", (GHOSTS_FILEPATH "blinky_middle_two.png"));
		//add sprites for title and start button
		//this->data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		//this->data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		background.setTexture(this->data->assets.getTexture("In Game Background"));
		//title.setTexture(this->data->assets.GetTexture("Game Title"));
		//playButton.setTexture(this->data->assets.GetTexture("Play Button"));

		//title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		//playButton.setPosition((SCREEN_WIDTH / 2) - (playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (playButton.getGlobalBounds().height / 2));
	}

	void InGameState::handleInput()
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

	void InGameState::update(float dt)
	{
		std::cout << "In game" << std::endl;
	}

	void InGameState::draw(float dt)
	{
		this->data->window.clear();
		this->background.setScale(20,20);
		this->data->window.draw(this->background);
		//this->data->window.draw(this->title);
		//this->data->window.draw(this->playButton);

		this->data->window.display();
	}
}
