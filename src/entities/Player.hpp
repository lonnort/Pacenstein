#pragma once

#include "Entity.hpp"
#include "Item.hpp"
#include "Definitions.hpp"
#include "Game.hpp"
#include <memory>

namespace Pacenstein {

    /**
     * The player is an entity that moves around in the map according to the user's input.
     *
     * A player has movement functions to react to input.
     */
    class Player : public Entity {
    public:
        /**
         * Constructor of the player class.
         *
         * Initializes member variables of the player class.
         */
        Player(game_data_ref_t data);

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
        void moveUp(const map_t worldMap);

        /**
         * Moves the player backwards.
         *
         * Updates the view so that the player position
         * is moved backwards. If the player is against
         * a wall, this function does nothing.
         */
        void moveDown(const map_t worldMap);

        /**
         * Checks if the player intersects with an Item. If they intersect, 
         * call the interact function of the item.
         * 
         * \param other The Item to check if the player collides with it.
         * \param data A reference to the game data object.
         * \return A bool of the collision. True if there is a collision, false if not.
         */
        bool intersect(Item & other, game_data_ref_t data);

        /**
         * Checks if the player is in range(less than 5 blocks away) of an Item.
         * 
         * \param other The Item to check if it is in range.
         * \return A bool of in range. True if the item is in range, false if not.
         */
        bool inRange(Item & other);

        /**
         * Returns the plane of the player.
         *
         * \return An sf::Vector2f of the plane.
         */
        sf::Vector2f getPlane();

        /**
         * Returns the x plane of the player.
         *
         * \return A double of the x plane.
         */
        [[deprecated]]
        double getPlaneX();

        /**
         * Returns the y plane of the player.
         *
         * \return A double of the y plane.
         */
        [[deprecated]]
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

    private:
        game_data_ref_t data;

        sf::Vector2f plane;
        double rotSpeed;
    };
}
