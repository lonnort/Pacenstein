#include "Inky.hpp"

namespace Pacenstein {
    Inky::Inky(float x, float y):
        Ghost(x, y),
        direction(4)
    {}

    Inky::Inky(sf::Vector2f xy):
        Inky(xy.x, xy.y)
    {}

    sf::Sprite Inky::getGhostSprite(game_data_ref_t data){
        inkySprite.setTexture(data->assets.getTexture(inkyDirections[direction]));
        return inkySprite;
    }
}
