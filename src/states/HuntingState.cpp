#include "Definitions.hpp"
#include "HuntingState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"

#include <iostream>

namespace Pacenstein {
	HuntingState::HuntingState(game_data_ref_t data) : data(data) {}

	void HuntingState::init() {
		this->data->assets.loadTexture("Hunting Background", (GHOSTS_FILEPATH "blinky_middle_one.png"));

		background.setTexture(this->data->assets.getTexture("Hunting Background"));
	}

	void HuntingState::handleInput() {
		sf::Event event;

		while (this->data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) this->data->window.close();

			if (sf::Event::KeyPressed == event.type) {
    			switch (event.key.code) {
					case sf::Keyboard::Key::KEY_EXIT:
						this->data->window.close();
						break;

					case sf::Keyboard::Key::KEY_PAUSE:
					case sf::Keyboard::Key::KEY_ALT_PAUSE:
						this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
						break;
					
					case sf::Keyboard::Key::Home:
						this->data->machine.addState(state_ref_t(std::make_unique<ScatterState>(this->data)), false);
						break;
				}
			}
		}
	}

	void HuntingState::update(float dt) {
		std::cout << "Hunting" << std::endl;
	}

	void HuntingState::draw(float dt){
		this->data->window.clear();
		this->background.setScale(20,20);
		this->data->window.draw(this->background);

		this->data->window.display();
	}
}
