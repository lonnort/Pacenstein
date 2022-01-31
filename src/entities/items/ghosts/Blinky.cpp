#include "Blinky.hpp"
#include <iostream>

namespace Pacenstein {
    Blinky::Blinky(float x, float y):
        Ghost(x, y),
        direction(1)
    {}

    Blinky::Blinky(sf::Vector2f xy):
        Blinky(xy.x, xy.y)
    {}

    sf::Sprite Blinky::getGhostSprite(game_data_ref_t data){
        blinkySprite.setTexture(data->assets.getTexture(blinkyDirections[direction]));
        return blinkySprite;
    }

    void Blinky::move(map_t worldMap){
        float movement_speed = 0.1;
        switch (this->direction){
        case 1:
            if((this->getPos().y - int(this->getPos().y)) > 0.5){
                std::cout << this->getPos().y << "\n";
            }else{
                this->position = {this->position.x, this->position.y + movement_speed};
            }
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:

            break;
            
        }
    }
}

