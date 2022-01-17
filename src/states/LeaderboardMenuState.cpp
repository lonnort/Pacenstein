#include "Definitions.hpp"
#include "LeaderboardMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Pacenstein {
	LeaderboardMenuState::LeaderboardMenuState(game_data_ref_t data) : data(data) { }

	void LeaderboardMenuState::init(){
        //Update to main menu background
		// this->data->assets.loadTexture("Leaderboard Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));

		//add sprites for title and start button
		this->data->assets.loadTexture("Leaderboard Title", (BUTTONS_FILEPATH "leaderboard.png"));
		this->data->assets.loadTexture("Back Button", "res/ui/button.png");

		// background.setTexture(this->data->assets.getTexture("Leaderboard Menu Background"));

		title.setTexture(this->data->assets.getTexture("Leaderboard Title"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
		backButton.setPosition((backButton.getGlobalBounds().width / 2), (backButton.getGlobalBounds().height / 2));
	}

	void LeaderboardMenuState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type){
				this->data->window.close();
			}

			if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window)){
				this->data->machine.removeState();
			}
		}
	}

	void LeaderboardMenuState::update(float dt){
		std::cout << "In leaderboard menu" << std::endl;
	}

	void LeaderboardMenuState::draw(float dt){
		this->data->window.clear();
		this->background.setScale(20,20);
		
		// this->data->window.draw(this->background);

		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		this->data->window.display();
	}
}
