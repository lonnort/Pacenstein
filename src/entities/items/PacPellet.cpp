#include "PacPellet.hpp"
#include <iostream>

namespace Pacenstein {
    PacPellet::PacPellet(float x, float y):
        Item(x, y, 10)
    {}

    PacPellet::PacPellet(sf::Vector2f xy):
        PacPellet(xy.x, xy.y)
    {}

    void PacPellet::interact(game_data_ref_t data) {
        collected = true;
        std::cout << "Collencted: " << collected << std::endl;
        data->score += points;
    }

    bool PacPellet::is_collected(){
        return collected;
    }

    sf::Vector2f PacPellet::getPosition(){
        return this->getPos();
    }
}
