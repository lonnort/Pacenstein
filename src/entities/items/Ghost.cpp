#include "Ghost.hpp"
#include <cmath>

namespace Pacenstein {
    Ghost::Ghost(float x, float y):
        Item(x, y, 200)
    {}

    Ghost::Ghost(sf::Vector2f xy):
        Ghost(xy.x, xy.y)
    {}

    void Ghost::interact(game_data_ref_t data) {
        //if scatter, += points, points *= 2 hoe points van andere ghost verhogen? remove ghost from map SCATTERING AND GHOSTSCORE IN DATA?
        //else
        if(data->scattering) {
            data->score += points * std::pow(2, data->ghostsEaten);
            data->ghostsEaten++;
        }
        else {
            data->lives--;
        }
    }
}
