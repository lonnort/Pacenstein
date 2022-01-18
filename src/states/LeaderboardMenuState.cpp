#include "Definitions.hpp"
#include "LeaderboardMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
	LeaderboardMenuState::LeaderboardMenuState(game_data_ref_t data) : data(data) {}

	void LeaderboardMenuState::parseScores(std::vector<std::string> file_content) {
		for (auto& line : file_content) {
			std::string player_name = "";
			int points = 0;

			std::stringstream ss(line);
			ss >> player_name >> points;
			player_name.pop_back();
			this->scores.push_back({player_name, points});
		}
		std::sort(scores.begin(), scores.end(), [](auto& l, auto& r){ return l.second > r.second; });
	}

	void LeaderboardMenuState::init() {
        //Update to main menu background
		// this->data->assets.loadTexture("Leaderboard Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));

		//add sprites for title and start button
		this->data->assets.loadTexture ("Leaderboard Title", (BUTTONS_FILEPATH "leaderboard.png"));
		this->data->assets.loadTexture ("Back Button", (BUTTONS_FILEPATH "back.png"));
		this->data->assets.loadTextFile("Scores", SCORE_FILEPATH);
		this->data->assets.loadFont("Font", FONT);

		sf::Font font = this->data->assets.getFont("Font");

		this->parseScores(this->data->assets.getTextFile("Scores"));

		for (auto& item : this->scores) {
			super_long_string += item.first + " " + std::to_string(item.second);
			if (item != *(this->scores.end()-1)) super_long_string += '\n';
		}

		// background.setTexture(this->data->assets.getTexture("Leaderboard Menu Background"));

		title.setTexture(this->data->assets.getTexture("Leaderboard Title"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
		backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);
	}

	void LeaderboardMenuState::handleInput() {
		sf::Event event;

		while (this->data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) { this->data->window.close(); }

			if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window)){
				this->data->machine.removeState();
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

	void LeaderboardMenuState::update(float dt) { std::cout << "In leaderboard menu" << std::endl; }

	void LeaderboardMenuState::draw(float dt) {
		this->data->window.clear();
		this->background.setScale(20, 20);
		
		// this->data->window.draw(this->background);

		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		sf::Text text(this->super_long_string, this->data->assets.getFont("Font"));
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		this->data->window.draw(text);

		this->data->window.display();
	}
}
