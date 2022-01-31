#include "Clyde.hpp"

namespace Pacenstein {
    Clyde::Clyde(float x, float y):
        Ghost(x, y),
        direction(4)
    {}

    Clyde::Clyde(sf::Vector2f xy):
        Clyde(xy.x, xy.y)
    {}

    sf::Sprite Clyde::getGhostSprite(game_data_ref_t data){
        clydeSprite.setTexture(data->assets.getTexture(clydeDirections[direction]));
        return clydeSprite;
    }
}
