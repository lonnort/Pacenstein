#include "Blinky.hpp"
#include <iostream>

namespace Pacenstein {
    Blinky::Blinky(float x, float y):
        Ghost(x, y)
    {}

    Blinky::Blinky(sf::Vector2f xy):
        Blinky(xy.x, xy.y)
    {}

    sf::Sprite Blinky::getGhostSprite(game_data_ref_t data){
        blinkySprite.setTexture(data->assets.getTexture(blinkyDirections[direction]));
        return blinkySprite;
    }

    sf::Vector2f Blinky::move(){
        float movement_speed = 0.1;
        switch (this->direction){
        case 1: // Noord
            if((this->getPos().y - int(this->getPos().y)) > 0.5){
                std::cout << this->getPos().y << "\n";
            }else{
                std::cout << this->getPos().y << "\n";
                this->position = {this->position.x, this->position.y + movement_speed};
            }
            break;

        case 2: // Oost
            break;

        case 3: // Zuid
            break;

        case 4:

            break;
            
        }
        return this->position;
    }
}

