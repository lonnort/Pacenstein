#include <sstream>
#include "Definitions.hpp"
#include "ScatterState.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Pacenstein {
	ScatterState::ScatterState(game_data_ref_t data) : data(data) { }

	void ScatterState::init(){
                //Update to main menu background
		this->data->assets.loadTexture("Scatter Background", SPLASH_BACKGROUND_FILEPATH);
		//add sprites for title and start button
		//this->data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		//this->data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		background.setTexture(this->data->assets.getTexture("Scatter Background"));
		//title.setTexture(this->data->assets.GetTexture("Game Title"));
		//playButton.setTexture(this->data->assets.GetTexture("Play Button"));

		//title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		//playButton.setPosition((SCREEN_WIDTH / 2) - (playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (playButton.getGlobalBounds().height / 2));
	}

	void ScatterState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type){
				this->data->window.close();
			}

			/*if (this->data->input.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
			{
				std::cout << "Go To Game Screen" << std::endl;
			}*/

			if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;

					case sf::Keyboard::Key::KEY_PAUSE:
					case sf::Keyboard::Key::KEY_ALT_PAUSE:
						this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
						break;

				}
			}
		}
	}

	void ScatterState::update(float dt){
		std::cout << "Scattering" << std::endl;
		if (this->clock.getElapsedTime().asSeconds() > 5)
            this->data->machine.removeState();
	}

	void ScatterState::draw(float dt){
		this->data->window.clear();

		this->data->window.draw(this->background);
		//this->data->window.draw(this->title);
		//this->data->window.draw(this->playButton);

		this->data->window.display();
	}
}
