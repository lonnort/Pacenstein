#include "Player.hpp"
#include <cmath>

namespace Pacenstein {
    Player::Player():
        Entity(2,2,-1,0,0),
        lives(3), score(0),
        planeX(0), planeY(.66),
        rotSpeed(0)
    {}

    void Player::moveLeft(){
        double oldDirX = this->dirX;
        this->dirX = this->dirX * std::cos(this->rotSpeed) - this->dirY * std::sin(this->rotSpeed);
        this->dirY = oldDirX * std::sin(this->rotSpeed) + this->dirY * std::cos(this->rotSpeed);
        double oldPlaneX = this->planeX;
        this->planeX = this->planeX * std::cos(this->rotSpeed) - this->planeY * std::sin(this->rotSpeed);
        this->planeY = oldPlaneX * std::sin(this->rotSpeed) + this->planeY * std::cos(this->rotSpeed);
    }

    void Player::moveRight(){
        double oldDirX = dirX;
        this->dirX = this->dirX * std::cos(-this->rotSpeed) - this->dirY * std::sin(-this->rotSpeed);
        this->dirY = oldDirX * std::sin(-this->rotSpeed) + this->dirY * std::cos(-this->rotSpeed);
        double oldPlaneX = planeX;
        this->planeX = this->planeX * std::cos(-this->rotSpeed) - this->planeY * std::sin(-this->rotSpeed);
        this->planeY = oldPlaneX * std::sin(-this->rotSpeed) + this->planeY * std::cos(-this->rotSpeed);
    }

    void Player::moveUp(const int worldMap[][19]){
        if(worldMap[int(posX + this->dirX * this->moveSpeed)][int(posY)] == false) posX += this->dirX * this->moveSpeed;
        if(worldMap[int(posX)][int(posY + this->dirY * this->moveSpeed)] == false) posY += this->dirY * this->moveSpeed;
    }

    void Player::moveDown(const int worldMap[][19]){
        if(worldMap[int(posX - this->dirX * this->moveSpeed)][int(posY)] == false) posX -= this->dirX * this->moveSpeed;
        if(worldMap[int(posX)][int(posY - this->dirY * this->moveSpeed)] == false) posY -= this->dirY * this->moveSpeed;
    }

    sf::Vector2f Player::getPos()   { return sf::Vector2f(this->posX, this->posY); }
    sf::Vector2f Player::getDir()   { return sf::Vector2f(this->dirX, this->dirY); }
    sf::Vector2f Player::getPlane() { return sf::Vector2f(this->planeX, this->planeY); }

    double Player::getPosX() { return this->posX; }
    double Player::getPosY() { return this->posY; }
    double Player::getDirX() { return this->dirX; }
    double Player::getDirY() { return this->dirY; }
    double Player::getPlaneX() { return this->planeX; }
    double Player::getPlaneY() { return this->planeY; }

    void Player::setMoveSpeed(const double newMoveSpeed) { this->moveSpeed = newMoveSpeed; }
    void Player::setRotSpeed (const double newRotSpeed)  { this->rotSpeed  = newRotSpeed; }

    void Player::addToScore(const unsigned int points) { this->score += points; }
    void Player::resetScore() { this->score = 0; }
    unsigned int Player::getScore() { return this->score; }

    void Player::removeLive() { this->lives--; }
    void Player::resetLives() { this->lives = 3; }
    unsigned int Player::getLives() { return this->lives; }
}
