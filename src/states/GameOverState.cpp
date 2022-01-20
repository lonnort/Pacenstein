#include "Definitions.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Pacenstein {
	GameOverState::GameOverState(game_data_ref_t data) : data(data) {}

	void GameOverState::init() {
		background.setTexture(this->data->assets.getTexture("Game Over Background"));
		title.setTexture(this->data->assets.getTexture("Game Over Title"));
		scoreText.setTexture(this->data->assets.getTexture("Score Text"));
		leaderboardText.setTexture(this->data->assets.getTexture("Leaderboard Text"));
		leaderboardPosition.setTexture(this->data->assets.getTexture("Leaderboard Position"));
		leaderboardName.setTexture(this->data->assets.getTexture("Leaderboard Name"));
		leaderboardScore.setTexture(this->data->assets.getTexture("Leaderboard Score"));
		backButton.setTexture(this->data->assets.getTexture("Back To Main Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2);
		scoreText.setPosition((SCREEN_WIDTH / 2) - (scoreText.getGlobalBounds().width / 2), 4 * (scoreText.getGlobalBounds().height / 2));
		leaderboardText.setPosition((SCREEN_WIDTH / 2) - (leaderboardText.getGlobalBounds().width / 2), 7 * (leaderboardText.getGlobalBounds().height / 2));
		leaderboardName.setPosition((SCREEN_WIDTH / 2) - (leaderboardName.getGlobalBounds().width / 2), 10 * (leaderboardName.getGlobalBounds().height / 2));
		leaderboardPosition.setPosition((SCREEN_WIDTH / 2) - (leaderboardName.getGlobalBounds().width / 2) - (leaderboardPosition.getGlobalBounds().width), 10 * (leaderboardName.getGlobalBounds().height / 2));
		leaderboardScore.setPosition((SCREEN_WIDTH / 2) - (leaderboardName.getGlobalBounds().width / 2) + (leaderboardScore.getGlobalBounds().width), 10 * (leaderboardName.getGlobalBounds().height / 2));
		backButton.setPosition((SCREEN_WIDTH / 2) - (backButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT) - 3 * (backButton.getGlobalBounds().height / 2));

		cursorHand.loadFromSystem(sf::Cursor::Hand);
		cursorArrow.loadFromSystem(sf::Cursor::Arrow);
	}

	void GameOverState::handleInput() {
		sf::Event event;

		while (this->data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) this->data->window.close();

			if(	this->data->input.isSpriteHovered(this->backButton, this->data->window))
				this->data->window.setMouseCursor(this->cursorHand);
			else this->data->window.setMouseCursor(this->cursorArrow);

			if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
				this->data->machine.addState(state_ref_t(std::make_unique<MainMenuState>(this->data)), true);

			if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;
				}
			}
		}
	}

	void GameOverState::update(float dt) {
		// std::cout << "game over!" << std::endl;
	}

	void GameOverState::draw(float dt) {
		this->data->window.clear();

		this->data->window.draw(this->background);
		this->data->window.draw(this->title);
		this->data->window.draw(this->scoreText);
		this->data->window.draw(this->leaderboardText);
		this->data->window.draw(this->leaderboardPosition);
		this->data->window.draw(this->leaderboardName);
		this->data->window.draw(this->leaderboardScore);
		this->data->window.draw(this->backButton);

		this->data->window.display();
	}
}
