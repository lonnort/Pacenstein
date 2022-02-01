#include "Pinky.hpp"

namespace Pacenstein {
    Pinky::Pinky(float x, float y):
        Ghost(x, y),
        direction(4)
    {}

    Pinky::Pinky(sf::Vector2f xy):
        Pinky(xy.x, xy.y)
    {}

    sf::Sprite Pinky::getGhostSprite(game_data_ref_t data){
        pinkySprite.setTexture(data->assets.getTexture(pinkyDirections[direction]));
        return pinkySprite;
    }
}
