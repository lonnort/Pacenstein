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
            if (sf::Event::Closed == event.type)
                this->data->window.close();
        }
    }

    void SplashState::update(float dt) {
        if (this->clock.getElapsedTime().asSeconds() > 3)
            this->data->machine.addState(state_ref_t(new MainMenuState(data)), true);
    }

    void SplashState::draw(float dt) {
        this->data->window.clear();
        this->data->window.draw(this->background);
        this->data->window.display();
    }
}
