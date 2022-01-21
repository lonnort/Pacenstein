#include "Definitions.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
	GameOverState::GameOverState(game_data_ref_t data) : data(data) {}

	void GameOverState::parseScores(std::vector<std::string> file_content) {
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

	void GameOverState::init() {
		sf::Font font = this->data->assets.getFont("Font");

		this->parseScores(this->data->assets.getCsvFile("Scores"));

		this->data->score = 690;
		for (int i = 0; i < scores.size(); i++) {
			if(this->data->score > scores[i].second){
				position = i;
				break;
			}
		}

		std::cout << position << "\n";

		if(position < 7){
			for(int i = 0; i < position; i++){
				positionString += std::to_string(i+1) + ".\n";
				nameString += scores[i].first + "\n";
				pointsString += std::to_string(scores[i].second) + "\n";
			}
			positionString += std::to_string(position+1) + ".\n";
			nameString += "<enter name>\n";
			pointsString += std::to_string(this->data->score) + "\n";
			if(scores.size() < 7){
				for(int i = position; i < scores.size(); i++){
					positionString += std::to_string(i+2) + ".\n";
					nameString += scores[i].first + "\n";
					pointsString += std::to_string(scores[i].second) + "\n";
				}
			}else{
				for(int i = position; i < 7; i++){
					positionString += std::to_string(i+2) + ".\n";
					nameString += scores[i].first + "\n";
					pointsString += std::to_string(scores[i].second) + "\n";
				}
			}
		}else{

		}

		title.setTexture(this->data->assets.getTexture("Game Over Title"));
		scoreText.setTexture(this->data->assets.getTexture("Score Text"));
		backButton.setTexture(this->data->assets.getTexture("Back To Main Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 30);
		scoreText.setPosition((SCREEN_WIDTH / 2) - (scoreText.getGlobalBounds().width / 2), 130);
		backButton.setPosition(50, 50);

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

		sf::Text leaderboardTitleText("position\tname\t\t\t points", this->data->assets.getFont("Font"));
		leaderboardTitleText.setOrigin(leaderboardTitleText.getGlobalBounds().width / 2, leaderboardTitleText.getGlobalBounds().height / 2);
		leaderboardTitleText.setPosition((SCREEN_WIDTH / 2), 250);

		sf::Text leaderboardPositionText(this->positionString, this->data->assets.getFont("Font"));
		leaderboardPositionText.setOrigin(leaderboardPositionText.getGlobalBounds().width / 2, leaderboardPositionText.getGlobalBounds().height / 2);
		leaderboardPositionText.setPosition((SCREEN_WIDTH / 2) -160, 400);

		sf::Text leaderboardNameText(this->nameString, this->data->assets.getFont("Font"));
		leaderboardNameText.setOrigin(leaderboardNameText.getGlobalBounds().width / 2, leaderboardNameText.getGlobalBounds().height / 2);
		leaderboardNameText.setPosition((SCREEN_WIDTH / 2), 400);

		sf::Text leaderboardPointsText(this->pointsString, this->data->assets.getFont("Font"));
		leaderboardPointsText.setOrigin(leaderboardPointsText.getGlobalBounds().width / 2, leaderboardPointsText.getGlobalBounds().height / 2);
		leaderboardPointsText.setPosition((SCREEN_WIDTH / 2) +170, 400);

		this->data->window.draw(leaderboardTitleText);
		this->data->window.draw(leaderboardPositionText);
		this->data->window.draw(leaderboardNameText);
		this->data->window.draw(leaderboardPointsText);

		this->data->window.draw(this->title);
		this->data->window.draw(this->scoreText);
		this->data->window.draw(this->backButton);

		this->data->window.display();
	}
}
