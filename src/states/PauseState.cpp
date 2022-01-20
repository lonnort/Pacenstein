#include "Definitions.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "SettingsMenuState.hpp"

#include <iostream>

namespace Pacenstein {
	PauseState::PauseState(game_data_ref_t data) : data(data) { }

	void PauseState::init(){
                //Update to main menu background
		// this->data->assets.loadTexture("Pause Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));
		//add sprites for title and start button

		// background.setTexture(this->data->assets.getTexture("Pause Background"));
		title.setTexture(this->data->assets.getTexture("Pause Title"));
		highscoreText.setTexture(this->data->assets.getTexture("Highscore Text"));
		giveUpButton.setTexture(this->data->assets.getTexture("Give Up Button"));
		continueButton.setTexture(this->data->assets.getTexture("Continue Button"));
		settingsButton.setTexture(this->data->assets.getTexture("Settings Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		highscoreText.setPosition((SCREEN_WIDTH / 2) - (highscoreText.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (highscoreText.getGlobalBounds().height / 2) - 200);
		continueButton.setPosition((SCREEN_WIDTH / 2) - (continueButton.getGlobalBounds().width / 2), 105 + (SCREEN_HEIGHT / 2) - (continueButton.getGlobalBounds().height / 2) + 2*(continueButton.getGlobalBounds().height));
		giveUpButton.setPosition((SCREEN_WIDTH / 2) - (giveUpButton.getGlobalBounds().width / 2) - 200, 100 + (SCREEN_HEIGHT / 2) - (continueButton.getGlobalBounds().height / 2) + 2*(continueButton.getGlobalBounds().height));
		settingsButton.setPosition((SCREEN_WIDTH / 2) - (settingsButton.getGlobalBounds().width / 2) + 200, 100 + (SCREEN_HEIGHT / 2) - (settingsButton.getGlobalBounds().height / 2) + 2*(settingsButton.getGlobalBounds().height));

		cursorHand.loadFromSystem(sf::Cursor::Hand);
		cursorArrow.loadFromSystem(sf::Cursor::Arrow);
	}

	void PauseState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type){
				this->data->window.close();
			}

			if(	this->data->input.isSpriteHovered(this->giveUpButton, this->data->window) ||
				this->data->input.isSpriteHovered(this->continueButton, this->data->window) ||
				this->data->input.isSpriteHovered(this->settingsButton, this->data->window))
				this->data->window.setMouseCursor(this->cursorHand);
			else this->data->window.setMouseCursor(this->cursorArrow);

			if (this->data->input.isSpriteClicked(this->continueButton, sf::Mouse::Left, this->data->window)){
				std::cout << "Continue game" << std::endl;
				this->data->machine.removeState();
			}

			if (this->data->input.isSpriteClicked(this->giveUpButton, sf::Mouse::Left, this->data->window)){
				std::cout << "Go To Game Over Screen" << std::endl;
				this->data->machine.addState(state_ref_t(std::make_unique<GameOverState>(this->data)), true);
			}

			if (this->data->input.isSpriteClicked(this->settingsButton, sf::Mouse::Left, this->data->window)){
				std::cout << "Go To Settings Screen" << std::endl;
				this->data->machine.addState(state_ref_t(std::make_unique<SettingsMenuState>(this->data)), false);
			}

			if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;

				}
			}
		}
	}

	void PauseState::update(float dt){
		std::cout << "Pause" << std::endl;
	}

	void PauseState::draw(float dt){
		this->data->window.clear();

		// this->data->window.draw(this->background);
		this->data->window.draw(this->title);
		this->data->window.draw(this->highscoreText);
		this->data->window.draw(this->giveUpButton);
		this->data->window.draw(this->continueButton);
		this->data->window.draw(this->settingsButton);

		this->data->window.display();
	}
}
