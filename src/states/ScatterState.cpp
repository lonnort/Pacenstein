#include <sstream>
#include "Definitions.hpp"
#include "ScatterState.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Pacenstein {
    ScatterState::ScatterState(game_data_ref_t data): HuntingState(data) {}

    void ScatterState::init(){
        this->data->scattering = true;
    }

    void ScatterState::update(float dt) {
        if (this->clock.getElapsedTime().asSeconds() > 5)
            this->data->machine.removeState();
    }
}
