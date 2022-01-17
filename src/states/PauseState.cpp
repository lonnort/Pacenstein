#include <sstream>
#include "Definitions.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Pacenstein
{
	PauseState::PauseState(game_data_ref_t data) : data(data) { }

	void PauseState::init()
	{
                //Update to main menu background
		this->data->assets.loadTexture("Pause Background", SPLASH_BACKGROUND_FILEPATH);
		//add sprites for title and start button
		//this->data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		//this->data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		background.setTexture(this->data->assets.getTexture("Pause Background"));
		//title.setTexture(this->data->assets.GetTexture("Game Title"));
		//playButton.setTexture(this->data->assets.GetTexture("Play Button"));

		//title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		//playButton.setPosition((SCREEN_WIDTH / 2) - (playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (playButton.getGlobalBounds().height / 2));
	}

	void PauseState::handleInput()
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

	void PauseState::update(float dt)
	{
		std::cout << "Pause" << std::endl;
	}

	void PauseState::draw(float dt)
	{
		this->data->window.clear();

		this->data->window.draw(this->background);
		//this->data->window.draw(this->title);
		//this->data->window.draw(this->playButton);

		this->data->window.display();
	}
}
