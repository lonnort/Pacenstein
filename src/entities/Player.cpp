#include "Player.hpp"
#include <cmath>
#include <iostream>

namespace Pacenstein {
    Player::Player(game_data_ref_t data):
        Entity(2,2,-1,0,0,0),
        data(data),
        plane({0.0, 0.66}),
        rotSpeed(0)
    {}

    void Player::moveLeft(){
        double oldDirX = this->direction.x;
        this->direction.x = this->direction.x * std::cos(this->rotSpeed) - this->direction.y * std::sin(this->rotSpeed);
        this->direction.y = oldDirX * std::sin(this->rotSpeed) + this->direction.y * std::cos(this->rotSpeed);
        double oldPlaneX = this->plane.x;
        this->plane.x = this->plane.x * std::cos(this->rotSpeed) - this->plane.y * std::sin(this->rotSpeed);
        this->plane.y = oldPlaneX * std::sin(this->rotSpeed) + this->plane.y * std::cos(this->rotSpeed);
    }

    void Player::moveRight(){
        double oldDirX = direction.x;
        this->direction.x = this->direction.x * std::cos(-this->rotSpeed) - this->direction.y * std::sin(-this->rotSpeed);
        this->direction.y = oldDirX * std::sin(-this->rotSpeed) + this->direction.y * std::cos(-this->rotSpeed);
        double oldPlaneX = plane.x;
        this->plane.x = this->plane.x * std::cos(-this->rotSpeed) - this->plane.y * std::sin(-this->rotSpeed);
        this->plane.y = oldPlaneX * std::sin(-this->rotSpeed) + this->plane.y * std::cos(-this->rotSpeed);
    }

    void Player::moveUp(const std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH> worldMap) {
        if (worldMap[int(position.x + this->direction.x * this->moveSpeed)][int(position.y)] == 0) position.x += this->direction.x * this->moveSpeed;
        if (worldMap[int(position.x)][int(position.y + this->direction.y * this->moveSpeed)] == 0) position.y += this->direction.y * this->moveSpeed;
    }

    void Player::moveDown(const std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH> worldMap) {
        if (worldMap[int(position.x - this->direction.x * this->moveSpeed)][int(position.y)] == 0) position.x -= this->direction.x * this->moveSpeed;
        if (worldMap[int(position.x)][int(position.y - this->direction.y * this->moveSpeed)] == 0) position.y -= this->direction.y * this->moveSpeed;
    }
    
    bool Player::intersect(Item & other, game_data_ref_t data){
        bool collision = int(this->position.x) == int(other.getPos().x) && int(this->position.y) == int(other.getPos().y);
        if(collision) other.interact(this->data);
        return collision;
    }

    bool Player::inRange(Item & other){
        sf::RectangleShape playerRect;
        playerRect.setPosition(sf::Vector2f(this->position.x - 5, this->position.y - 5));
        playerRect.setSize(sf::Vector2f(10.0, 10.0));
        return playerRect.getGlobalBounds().contains(other.getPos());
    }

    sf::Vector2f Player::getPlane() { return sf::Vector2f(this->plane.x, this->plane.y); }

    double Player::getPlaneX() { return this->plane.x; }
    double Player::getPlaneY() { return this->plane.y; }

    void Player::setMoveSpeed(const double newMoveSpeed) { this->moveSpeed = newMoveSpeed; }
    void Player::setRotSpeed (const double newRotSpeed)  { this->rotSpeed  = newRotSpeed; }
}
