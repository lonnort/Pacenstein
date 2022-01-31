#include "Blinky.hpp"

namespace Pacenstein {
    Blinky::Blinky(float x, float y):
        Ghost(x, y),
        direction(4)
    {}

    Blinky::Blinky(sf::Vector2f xy):
        Blinky(xy.x, xy.y)
    {}

    sf::Sprite Blinky::getGhostSprite(game_data_ref_t data){
        blinkySprite.setTexture(data->assets.getTexture(blinkyDirections[direction]));
        return blinkySprite;
    }
}

