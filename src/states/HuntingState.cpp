#include "Definitions.hpp"
#include "HuntingState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"

namespace Pacenstein {
    HuntingState::HuntingState(game_data_ref_t data) : InGameState(data) {}

    void HuntingState::handleInput() {
        sf::Event event;

        while (this->data->window.pollEvent(event)) {
            this->data->window.setMouseCursorVisible(false);

            if (sf::Event::Closed == event.type) this->data->window.close();

            if (sf::Event::KeyPressed == event.type) {
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown)) {
                    this->data->lives--;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_EXIT)) {
                    this->data->window.close();
                }
            }
        }
    }

    void HuntingState::update(float dt) {
        // testing ding
        this->data->score++;
    }
}
