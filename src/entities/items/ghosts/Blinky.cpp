#include "Blinky.hpp"
#include <iostream>
#include <cstdlib>

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

    sf::Vector2f Blinky::move(const map_t & worldMap){
        float movement_speed = 0.01;
        // std::vector<std::vector<float>> directions = {{0.0, -1.0}, {1.0, 0.0}, {0.0, 1.0}, {-1.0, 0.0}}; //remove current direction?

        // auto it = std::find(directions.begin(), directions.end(), this->direction);
        // uint dir = it - directions.begin();
        // std::cout << dir;

        // uint dir = -1;
        // for(unsigned int i = 0; i < directions.size(); i++){
        //     if ( int(this->direction.x) == int(directions[i][0]) && int(this->direction.y) == int(directions[i][1]) ){
        //         dir = i;
        //     }
        // }

        switch (this->direction){
            case 1: // Noord
                if((this->position.y - int(this->position.y)) < 0.5){
                    if(worldMap[int(this->position.y) - 1][int(this->position.x)] == 1) { //if block above ghost is a wall
                        this->direction = rand() % 4 + 1;
                        // std::cout << "direction x: " << this->direction.x << " direction y: " << this->direction.y;
                        break;
                    }
                }
                // std::cout << this->getPos().y << "\n";
                this->position = {this->position.x, this->position.y - movement_speed};
                break;

            case 2: // Oost
                if((this->position.x - int(this->position.x)) > 0.5){
                    if(worldMap[int(this->position.y)][int(this->position.x) + 1] == 1) { //if block right of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        // std::cout << "direction x: " << this->direction.x << " direction y: " << this->direction.y;
                        break;
                    }
                }
                // std::cout << this->getPos().y << "\n";
                this->position = {this->position.x + movement_speed, this->position.y};
                break;

            case 3: // Zuid
                if((this->position.y - int(this->position.y)) > 0.5){
                    if(worldMap[int(this->position.y) + 1][int(this->position.x)] == 1) { //if block below ghost is a wall
                        this->direction = rand() % 4 + 1;
                        // std::cout << "direction x: " << this->direction.x << " direction y: " << this->direction.y;
                        break;
                    }
                }
                // std::cout << this->getPos().y << "\n";
                this->position = {this->position.x, this->position.y + movement_speed};
                break;

            case 4: // West
                if((this->position.x - int(this->position.x)) < 0.5){
                    if(worldMap[int(this->position.y)][int(this->position.x) - 1] == 1) { //if block left of ghost is a wall
                        this->direction = rand() % 4 + 1;
                        // std::cout << "direction x: " << this->direction.x << " direction y: " << this->direction.y;
                        break;
                    }
                }
                // std::cout << this->getPos().y << "\n";
                this->position = {this->position.x - movement_speed, this->position.y};
                break;
        }
        return this->position;
    }
}

