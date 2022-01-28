#include "Player.hpp"
#include <cmath>
#include <iostream>

namespace Pacenstein {
    Player::Player():
        Entity(2,2,-1,0,0,0),
        lives(3),
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
        int px = position.x + this->direction.x * this->moveSpeed;
        int py = position.y;
        if (worldMap[px][py] == 0 || worldMap[px][py] == 3 || worldMap[px][py] == 4) {
            position.x += this->direction.x * this->moveSpeed;
        }

        px = position.x;
        py = position.y + this->direction.y * this->moveSpeed;
        if (worldMap[px][py] == 0 || worldMap[px][py] == 3 || worldMap[px][py] == 4) {
            position.y += this->direction.y * this->moveSpeed;
        }
    }

    void Player::moveDown(const std::array<std::array<int, MAP_HEIGHT>, MAP_WIDTH> worldMap) {
        int px = position.x - this->direction.x * this->moveSpeed;
        int py = position.y;
        if (worldMap[px][py] == 0 || worldMap[px][py] == 3 || worldMap[px][py] == 4) {
            position.x -= this->direction.x * this->moveSpeed;
        }

        px = position.x;
        py = position.y - this->direction.y * this->moveSpeed;
        if (worldMap[px][py] == 0 || worldMap[px][py] == 3 || worldMap[px][py] == 4) {
            position.y -= this->direction.y * this->moveSpeed;
        }
    }

    bool Player::collide(Entity other){
        return this->getGlobalBounds().intersects(other.getGlobalBounds());
    }

    sf::Vector2f Player::getPlane() { return sf::Vector2f(this->plane.x, this->plane.y); }

    double Player::getPlaneX() { return this->plane.x; }
    double Player::getPlaneY() { return this->plane.y; }

    void Player::setMoveSpeed(const double newMoveSpeed) { this->moveSpeed = newMoveSpeed; }
    void Player::setRotSpeed (const double newRotSpeed)  { this->rotSpeed  = newRotSpeed; }

    void Player::removeLive() { this->lives--; }
    void Player::resetLives() { this->lives = 3; }
    unsigned int Player::getLives() { return this->lives; }
}
