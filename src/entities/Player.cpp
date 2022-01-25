#include "Player.hpp"
#include <cmath>

namespace Pacenstein {
    Player::Player():
        Entity(2,2,0,0-1,0,0),
        lives(3), score(0),
        plane(sf::Vector2f(0.0f, 0.66f)),
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

    sf::Vector2f Player::getPos()   { return sf::Vector2f(this->position.x, this->position.y); }
    sf::Vector2f Player::getDir()   { return sf::Vector2f(this->direction.x, this->direction.y); }
    sf::Vector2f Player::getPlane() { return sf::Vector2f(this->plane.x, this->plane.y); }

    double Player::getPosX() { return this->position.x; }
    double Player::getPosY() { return this->position.y; }
    double Player::getDirX() { return this->direction.x; }
    double Player::getDirY() { return this->direction.y; }
    double Player::getPlaneX() { return this->plane.x; }
    double Player::getPlaneY() { return this->plane.y; }

    void Player::setMoveSpeed(const double newMoveSpeed) { this->moveSpeed = newMoveSpeed; }
    void Player::setRotSpeed (const double newRotSpeed)  { this->rotSpeed  = newRotSpeed; }

    void Player::addToScore(const unsigned int points) { this->score += points; }
    void Player::resetScore() { this->score = 0; }
    unsigned int Player::getScore() { return this->score; }

    void Player::removeLive() { this->lives--; }
    void Player::resetLives() { this->lives = 3; }
    unsigned int Player::getLives() { return this->lives; }
}
