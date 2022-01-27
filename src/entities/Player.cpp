#include "Player.hpp"
#include <cmath>

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

    void Player::moveUp(const int worldMap[][19]){
        if(worldMap[int(position.x + this->direction.x * this->moveSpeed)][int(position.y)] == false) position.x += this->direction.x * this->moveSpeed;
        if(worldMap[int(position.x)][int(position.y + this->direction.y * this->moveSpeed)] == false) position.y += this->direction.y * this->moveSpeed;
    }

    void Player::moveDown(const int worldMap[][19]){
        if(worldMap[int(position.x - this->direction.x * this->moveSpeed)][int(position.y)] == false) position.x -= this->direction.x * this->moveSpeed;
        if(worldMap[int(position.x)][int(position.y - this->direction.y * this->moveSpeed)] == false) position.y -= this->direction.y * this->moveSpeed;
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
