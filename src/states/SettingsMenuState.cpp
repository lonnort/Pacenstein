#include "Definitions.hpp"
#include "SettingsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>
#include <sstream>

namespace Pacenstein {
	SettingsMenuState::SettingsMenuState(game_data_ref_t data) : data(data) {}

	void SettingsMenuState::parseSettings(std::vector<std::string> file_content) {
		bool keybinds = false;
		bool alt_keys = false;
		bool window = false;

		for (auto& line : file_content) {
			std::string setting = "";
			std::string eq = "";
			std::string value = "";

			std::stringstream ss(line);
			ss >> setting >> eq >> value;

			if (eq == "" && value == "") {
				if (setting == "[keybindings]") {
					keybinds = true;
					alt_keys = false;
					window = false;
				}
				else if (setting == "[keybindings.alt]") {
					keybinds = false;
					alt_keys = true;
					window = false;
				}
				else if (setting == "[window]") {
					keybinds = false;
					alt_keys = false;
					window = true;
				}
			}
			else if (eq == "=" && value != "") {
				if (keybinds) {
					if (value.size() == 1)
						this->settings.push_back({"Move " + setting, value});
					else this->settings.push_back({setting, value});
				}
				else if (alt_keys)
					this->settings.push_back({"Move " + setting + " alt", value});
				// else if (window)
				// 	this->settings.push_back({setting, value});
			}
		}
		for (auto& s : settings) std::cout << s[0] << " " << s[1] << std::endl;
	}

	void SettingsMenuState::init() {
		sf::Font font = this->data->assets.getFont("Font");
		this->parseSettings(this->data->assets.getConfFile("Settings"));

		std::string path = "";
		int offset = 0;
		for (auto& setting : this->settings) {
			path = BUTTONS_FILEPATH + setting[1] + "_key.png";

			std::cout << setting[0] << std::endl;

			sf::Sprite tmp;
			tmp.setTexture(this->data->assets.getTexture(setting[0]));
			if (setting[0].find("alt") == -1) {
				tmp.setPosition((SCREEN_WIDTH / 2) + 20, 200 + offset);
				super_long_string += setting[0];
			}
			else {
				static bool first = true;
				if (first) {
					offset = 0;
					first = false;
				}
				tmp.setPosition((SCREEN_WIDTH / 2) + 100, 200 + offset);
			}
			offset += 60;
			this->sprites.push_back(tmp);

			if (setting != *(this->settings.end()-1)) super_long_string += "\n\n";

			cursorHand.loadFromSystem(sf::Cursor::Hand);
			cursorArrow.loadFromSystem(sf::Cursor::Arrow);
		}

		title.setTexture(this->data->assets.getTexture("Settings Text"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
		backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);
	}

	void SettingsMenuState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
			if (sf::Event::Closed == event.type) this->data->window.close();

			if (this->data->input.isSpriteHovered(this->backButton, this->data->window)){
				this->data->window.setMouseCursor(this->cursorHand);
			}
			else{
				this->data->window.setMouseCursor(this->cursorArrow);
			}

			if (this->data->input.isSpriteClicked(this->backButton, sf::Mouse::Left, this->data->window))
				this->data->machine.removeState();

			if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;
				}
			}
		}
	}

	void SettingsMenuState::update(float dt) {}

	void SettingsMenuState::draw(float dt) {
		this->data->window.clear();

		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		for(auto sp : this->sprites) this->data->window.draw(sp);

		sf::Text text(this->super_long_string, this->data->assets.getFont("Font"));
		text.setPosition(SCREEN_WIDTH / 2 -200, 190);
		this->data->window.draw(text);

		this->data->window.display();
	}
}
