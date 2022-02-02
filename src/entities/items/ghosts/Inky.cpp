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

    sf::Vector2f Inky::move(const map_t & worldMap){
        float movement_speed = 0.01;

        switch (this->direction){
            case 1: // Noord
                if((this->position.y - int(this->position.y)) < 0.5){
                    if(worldMap[int(this->position.x)][int(this->position.y) - 1] == 3) { //if block above ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x, this->position.y - movement_speed};
                break;

            case 2: // Oost
                if((this->position.x - int(this->position.x)) > 0.5){
                    if(worldMap[int(this->position.x) + 1][int(this->position.y)] == 3) { //if block right of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x + movement_speed, this->position.y};
                break;

            case 3: // Zuid
                if((this->position.y - int(this->position.y)) > 0.5){
                    if(worldMap[int(this->position.x)][int(this->position.y) + 1] == 3) { //if block below ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x, this->position.y + movement_speed};
                break;

            case 4: // West
                if((this->position.x - int(this->position.x)) < 0.5){
                    if(worldMap[int(this->position.x) - 1][int(this->position.y)] == 3) { //if block left of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x - movement_speed, this->position.y};
                break;
        }
        return this->position;
    }
}
