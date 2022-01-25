#include "Definitions.hpp"
#include "HuntingState.hpp"
#include "PauseState.hpp"
#include "ScatterState.hpp"

namespace Pacenstein {
    HuntingState::HuntingState(game_data_ref_t data) : InGameState(data), data(data) {}

    // void HuntingState::init() {}

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
                    this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown)) {
                    player.removeLive();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_EXIT)) {
                    this->data->window.close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Home)) {
                    // for testing purposes only
                    if (huntingState) {
                        this->data->machine.addState(state_ref_t(std::make_unique<ScatterState>(this->data)), false);
                    }
                }
            }
        }
    }

    void HuntingState::update(float dt) {
        this->data->score++;
    }

    // void HuntingState::draw(float dt) {
    //     this->data->window.clear();
    //     this->data->window.draw();

    //     this->data->window.display();
    // }
}
