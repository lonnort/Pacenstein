#include "Definitions.hpp"
#include "SettingsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
	SettingsMenuState::SettingsMenuState(game_data_ref_t data) : data(data) { }

	void SettingsMenuState::parseSettings(std::vector<std::string> file_content) {
		for (auto& line : file_content) {
			std::string action = "";
			std::string first_word = "";
			std::string second_word = "";
			std::string third_word = "";

			std::stringstream ss(line);
			ss >> action >> first_word >> second_word >> third_word;

			if(third_word == "" and second_word == ""){
				action.pop_back();
				this->settings.push_back({action, first_word});
			}else if(third_word == ""){
				action += " " + first_word;
				action.pop_back();
				this->settings.push_back({action, second_word});
			}else{
				action += " " + first_word;
				action.pop_back();
				second_word.pop_back();
				this->settings.push_back({action, second_word, third_word});
			}
			
		}
	}

	void SettingsMenuState::init() {
        //Update to main menu background
		// this->data->assets.loadTexture("Settings Menu Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));

		//add sprites for title and back button
		this->data->assets.loadTexture("Settings Title", (BUTTONS_FILEPATH "settings.png"));
		this->data->assets.loadTexture("Back Button", (BUTTONS_FILEPATH "back.png"));
		this->data->assets.loadTextFile("Scores", "src/data/settings.ini");
		this->data->assets.loadFont("Font", FONT);

		sf::Font font = this->data->assets.getFont("Font");

		this->parseSettings(this->data->assets.getTextFile("Scores"));

		std::string path = "";
		int offset = 0;
		for (auto& item : this->settings) {
			path = BUTTONS_FILEPATH + item[1];
			this->data->assets.loadTexture(item[0], path);

			sf::Sprite tmp;
			tmp.setTexture(this->data->assets.getTexture(item[0]));
			tmp.setPosition((SCREEN_WIDTH / 2), 200 + offset);
			this->sprites.push_back(tmp);

			if(item.size() == 3){
				path = BUTTONS_FILEPATH + item[2];
				this->data->assets.loadTexture((item[0] + " alt"), path);

				tmp.setTexture(this->data->assets.getTexture(item[0] + " alt"));
				tmp.setPosition((SCREEN_WIDTH / 2) + 100, 200 + offset);
				this->sprites.push_back(tmp);
			}

			offset += 60;

			super_long_string += item[0];
			if (item != *(this->settings.end()-1)) super_long_string += "\n\n";
		}

		// background.setTexture(this->data->assets.getTexture("Settings Menu Background"));

		title.setTexture(this->data->assets.getTexture("Settings Title"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
		backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);
	}

	void SettingsMenuState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type){
				this->data->window.close();
			}

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

	void SettingsMenuState::update(float dt){
		// std::cout << "In settings menu" << std::endl;
	}

	void SettingsMenuState::draw(float dt){
		this->data->window.clear();

		// this->background.setScale(20,20);
		// this->data->window.draw(this->background);

		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		for(auto sp : this->sprites){
			this->data->window.draw(sp);
		}

		sf::Text text(this->super_long_string, this->data->assets.getFont("Font"));
		// text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(SCREEN_WIDTH / 2 -200, 190);
		this->data->window.draw(text);

		this->data->window.display();
	}
}
