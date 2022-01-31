#include "PacPellet.hpp"

namespace Pacenstein {
    PacPellet::PacPellet(float x, float y):
        Item(x, y, 10)
    {}

    PacPellet::PacPellet(sf::Vector2f xy):
        PacPellet(xy.x, xy.y)
    {}

    void PowerPellet::interact(game_data_ref_t data) {
        //remove pellet from map
        data->score += points;
    }
}
