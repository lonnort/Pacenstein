#include "Player.hpp"
#include <cmath>

namespace Pacenstein {
    Player::Player(){
        //call entity constructor
    }

    unsigned int Player::getLives(){
        return this->lives;
    }
    
    unsigned int Player::getScore(){
        return this->score;
    }

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

    double Player::getPosX(){
        return this->posX;
    }

    double Player::getPosY(){
        return this->posY;
    }

    double Player::getDirX(){
        return this->dirX;
    }

    double Player::getDirY(){
        return this->dirY;
    }

    double Player::getPlaneX(){
        return this->planeX;
    }

    double Player::getPlaneY(){
        return this->planeY;
    }

    void Player::setMoveSpeed(const double newMoveSpeed){
        this->moveSpeed = newMoveSpeed;
    }

    void Player::setRotSpeed(const double newRotSpeed){
        this->rotSpeed = newRotSpeed;
    }

    void Player::addToScore(const unsigned int points){
        this->score += points;
    }

    void Player::removeLive(){
        this->lives--;
    }

    void Player::resetLives(){
        this->lives = 3;
    }

    void Player::resetScore(){
        this->score = 0;
    }
}
