#include <iostream>
#include "SplashState.hpp"
#include "Definitions.hpp"
#include "MainMenuState.hpp"

//#define SPLASH_BACKGROUND_FILEPATH "res/splash/background.png"

namespace Pacenstein {
    SplashState::SplashState(game_data_ref_t data) : data(data) {}

    void SplashState::init() {
        this->data->assets.loadTexture("Splash Background", SPLASH_BACKGROUND_FILEPATH);
        this->background.setTexture(this->data->assets.getTexture("Splash Background"));
    }

    void SplashState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type){
                this->data->window.close();
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

    void SplashState::update(float dt) {
        if (this->clock.getElapsedTime().asSeconds() > 1)
            this->data->machine.addState(state_ref_t(std::make_unique<MainMenuState>(data)), true);
    }

    void SplashState::draw(float dt) {
        this->data->window.clear();
        this->data->window.draw(this->background);
        this->data->window.display();
    }
}
