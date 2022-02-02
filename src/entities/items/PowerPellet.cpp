#include "PowerPellet.hpp"
#include "ScatterState.hpp"
#include <memory>

namespace Pacenstein {
    PowerPellet::PowerPellet(float x, float y):
        Item(x, y, 100)
    {}

    PowerPellet::PowerPellet(sf::Vector2f xy):
        PowerPellet(xy.x, xy.y)
    {}

    void PowerPellet::interact(game_data_ref_t data) {
        collected = true;
        data->score += points;
        data->machine.addState(state_ref_t(std::make_unique<ScatterState>(data)), false);
    }

    bool PowerPellet::is_collected(){
        return collected;
    }

    sf::Vector2f PowerPellet::getPosition(){
        return this->getPos();
    }
}
