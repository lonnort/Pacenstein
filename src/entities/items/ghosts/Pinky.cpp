#include "Pinky.hpp"

namespace Pacenstein {
    Pinky::Pinky(float x, float y, float speed):
        Ghost(x, y),
        direction(4),
        movement_speed(speed)
    {}

    Pinky::Pinky(sf::Vector2f xy, float speed):
        Pinky(xy.x, xy.y, speed)
    {}

    sf::Sprite Pinky::getGhostSprite(game_data_ref_t data){
        pinkySprite.setTexture(data->assets.getTexture(pinkyDirections[direction]));
        return pinkySprite;
    }     

    int Pinky::getDirection(){
        return this->direction;
    }

    sf::Vector2f Pinky::move(const map_t & worldMap){
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
                if((this->position.x - int(this->position.x)) < 0.5){
                    if(worldMap[int(this->position.x) - 1][int(this->position.y)] == 3) { //if block left of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x - movement_speed, this->position.y};
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
                if((this->position.x - int(this->position.x)) > 0.5){
                    if(worldMap[int(this->position.x) + 1][int(this->position.y)] == 3) { //if block right of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        break;
                    }
                }
                this->position = {this->position.x + movement_speed, this->position.y};
                break;
        }
        return this->position;
    }

    bool Pinky::is_collected(){
        return collected;
    }
}
