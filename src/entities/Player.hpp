#pragma once

#include "Entity.hpp"

namespace Pacenstein {
    /**
     * The player is an entity that moves around in the map according to the user's input.
     *
     * A player has movement functions to react to input, 
     * 3 lives and a score.
     */
    class Player : public Entity {
    public:
        /**
         * Constructor of the player class.
         *
         * Initializes member variables of the player class.
         */
        Player();

        /**
         * Returns the number of lives of the player.
         *
         * \return An unsigned int of the number of lives.
         */
        unsigned int getLives();

        /**
         * Returns the score of the player.
         *
         * \return An unsigned int of the score.
         */
        unsigned int getScore();

        /**
         * Turns the player to the left.
         *
         * Updates the view so that the player camera faces
         * more to the left.
         */
        void moveLeft();

        /**
         * Turns the player to the right.
         *
         * Updates the view so that the player camera faces
         * more to the right.
         */
        void moveRight();

        /**
         * Moves the player forward.
         *
         * Updates the view so that the player position
         * is moved forwards. If the player is against
         * a wall, this function does nothing.
         */
        void moveUp(const int worldMap[][19]);

        /**
         * Moves the player backwards.
         *
         * Updates the view so that the player position
         * is moved backwards. If the player is against
         * a wall, this function does nothing.
         */
        void moveDown(const int worldMap[][19]);

        /***/
        sf::Vector2f getPos();

        /***/
        sf::Vector2f getDir();

        /***/
        sf::Vector2f getPlane();

        /**
         * Returns the x position of the player.
         *
         * \return A double of the x position.
         */
        double getPosX();

        /**
         * Returns the y position of the player.
         *
         * \return A double of the y position.
         */
        double getPosY();

        /**
         * Returns the x direction of the player.
         *
         * \return A double of the x direction.
         */
        double getDirX();

        /**
         * Returns the y direction of the player.
         *
         * \return A double of the y direction.
         */
        double getDirY();

        /**
         * Returns the x plane of the player.
         *
         * \return A double of the x plane.
         */
        double getPlaneX();

        /**
         * Returns the y plane of the player.
         *
         * \return A double of the y plane.
         */
        double getPlaneY();

        /**
         * Sets the moveSpeed of the player to a new move speed.
         *
         * \param newMoveSpeed A const double of the new move speed.
         */
        void setMoveSpeed(const double newMoveSpeed);

        /**
         * Sets the rotSpeed of the player to a new rotation speed.
         *
         * \param newRotSpeed A const double of the new rotation speed.
         */
        void setRotSpeed(const double newRotSpeed);

        /**
         * Adds the points of a fruit/pellet/ghost to the score
         * of the player.
         *
         * \param points An unsigned int to add to the score.
         */
        void addToScore(unsigned int points);

        /**
         * Removes one live of the player.
         */
        void removeLive();

        /**
         * Resets the lives of the player back to the 
         * original value of 3.
         * 
         * Used when a new game is started.
         */
        void resetLives();

        /**
         * Resets the score of the player back to the 
         * original value of 0.
         * 
         * Used when a new game is started.
         */
        void resetScore();
        
    private:
    	unsigned int lives, score;
        double planeX, planeY;
        double rotSpeed;
    };
}
