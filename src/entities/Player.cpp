#include "Player.hpp"

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

    }

    void Player::moveRight(){
        
    }

    void Player::moveUp(){
        
    }

    void Player::moveDown(){
        
    }

    void Player::addToScore(unsigned int points){
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
