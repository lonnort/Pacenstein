#include <sstream>
#include "Definitions.hpp"
#include "ScatterState.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Pacenstein {
    ScatterState::ScatterState(game_data_ref_t data) : HuntingState(data), data(data) {}

    // void ScatterState::init() {}

    // void ScatterState::handleInput() {
    //     sf::Event event;

    //     while (this->data->window.pollEvent(event)) {
    //         this->data->window.setMouseCursorVisible(false);

    //         if (sf::Event::Closed == event.type) this->data->window.close();

    //         if (sf::Event::KeyPressed == event.type) {
    //             switch (event.key.code) {
    //                 case sf::Keyboard::Key::KEY_EXIT:
    //                     this->data->window.close();
    //                     break;

    //                 case sf::Keyboard::Key::KEY_PAUSE:
    //                 case sf::Keyboard::Key::KEY_ALT_PAUSE:
    //                     this->data->machine.addState(state_ref_t(std::make_unique<PauseState>(this->data)), false);
    //                     break;
    //             }
    //         }
    //     }
    // }

    void ScatterState::update(float dt) {
        // std::cout << "Scattering" << std::endl;
        if (this->clock.getElapsedTime().asSeconds() > 5)
            this->data->machine.removeState();
    }

    // void ScatterState::draw(float dt) {
    //     sf::Text scatter("scatter", this->data->assets.getFont("Font"));
    //     scatter.setPosition(5, 50);
    //     this->data->window.draw(scatter);
    //     HuntingState::draw(dt);
    // }
}
