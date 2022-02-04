#include "Definitions.hpp"
#include "HuntingState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"
#include "GameOverState.hpp"
#include <iostream>

namespace Pacenstein {
    HuntingState::HuntingState(game_data_ref_t data): InGameState(data) {}

    void HuntingState::init(){}

    void HuntingState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(false);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown)) {
                this->data->lives--;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_EXIT)) {
                this->data->window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP)
        ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_UP)) {
            this->move("up");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN)
        ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_DOWN)) {
            this->move("down");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)
        ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_RIGHT)) {
            this->move("right");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT)
        ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_LEFT)) {
            this->move("left");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_PAUSE)
        ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_ALT_PAUSE)) {
            this->generatePauseBackground();
            this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
        }
    }

    void HuntingState::update(float dt) {
        if(this->data->scattering and first_spo){
            clock.restart();
            first_spo = false;
        }
        if (this->clock.getElapsedTime().asSeconds() > 15) {
            clock.restart();
            white_spooks = true;
        }
        if (this->clock.getElapsedTime().asSeconds() > 2 and white_spooks){
            this->data->scattering = false;
            first_spo = true;
            white_spooks = false;
        }

        if(this->data->invincible and first_inv){
            clock.restart();
            first_inv = false;
        }
        if (this->clock.getElapsedTime().asSeconds() > 2){
            this->data->invincible = false;
            first_inv = true;
        }

        if(this->data->pacPelletsLeft == 0 && this->data->powerPelletsLeft == 0 && !this->data->scattering){
            this->data->machine.addState(state_ref_t(std::make_unique<GameOverState>(this->data)), true);
        }

        if(this->spooks_clock.getElapsedTime().asMilliseconds() > 300){
            spooks_one = !spooks_one;
            this->spooks_clock.restart();
        }
    }
}
