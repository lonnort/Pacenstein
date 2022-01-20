#include "Definitions.hpp"
#include "CreditsMenuState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Pacenstein {
	CreditsMenuState::CreditsMenuState(game_data_ref_t data) : data(data) {}

	void CreditsMenuState::init() {
		title.setTexture(this->data->assets.getTexture("Credits Title"));
		backButton.setTexture(this->data->assets.getTexture("Back Button"));

		title.setPosition((SCREEN_WIDTH / 2) - (title.getGlobalBounds().width / 2), title.getGlobalBounds().height / 2 + 50);
		backButton.setPosition((backButton.getGlobalBounds().width / 2) + 50, (backButton.getGlobalBounds().height / 2) + 50);

		cursorHand.loadFromSystem(sf::Cursor::Hand);
		cursorArrow.loadFromSystem(sf::Cursor::Arrow);
	}

	void CreditsMenuState::handleInput() {
		sf::Event event;

		while (this->data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) this->data->window.close();

			if (this->data->input.isSpriteHovered(this->backButton, this->data->window))
				this->data->window.setMouseCursor(this->cursorHand);
			else this->data->window.setMouseCursor(this->cursorArrow);

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

	void CreditsMenuState::update(float dt) {
		// std::cout << "In credits menu" << std::endl;
	}

	void CreditsMenuState::draw(float dt) {
		this->data->window.clear();
		this->background.setScale(20, 20);

		this->data->window.draw(this->title);
		this->data->window.draw(this->backButton);

		this->data->window.display();
	}
}

