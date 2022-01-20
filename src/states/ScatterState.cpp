#include <sstream>
#include "Definitions.hpp"
#include "ScatterState.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Pacenstein {
	ScatterState::ScatterState(game_data_ref_t data) : data(data) {}

	void ScatterState::init() {
		this->data->assets.loadTexture("Scatter Background", BACKGROUND_FILEPATH);
		background.setTexture(this->data->assets.getTexture("Scatter Background"));
	}

	void ScatterState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)){
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
		this->data->window.display();
	}
}
