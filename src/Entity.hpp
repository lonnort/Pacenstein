#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace Pacenstein {
    /**
     * The class describing what anything that can be interacted with has to contain.
     *
     * Entities are items like fruits and pellets, ghosts, and the player itself.
     */
    class Entity {
    public:
        /**
         * Constructor of the Entity class.
         *
         * \param px The x position of the entity.
         * \param py The y position of the entity.
         * \param dx The x direction of the entity.
         * \param dy The y direction of the entity.
         * \param sx The size in the x direction of the entity.
         * \param sy The size in the y direction of the entity.
         * \param ms The move speed of the entity. Default is 0.
         */
        Entity(float px, float py, float dx, float dy, float sx, float sy, float ms = 0);

        /**
         * Constructor of the Entity class.
         *
         * \param pos  The position of the entity as an sf::Vector2f.
         * \param dir  The direction of the entity as an sf::Vector2f.
         * \param size The size of the entity as an sf::Vector2f.
         * \param ms   The move speed of the entity. Default is 0.
         */
        Entity(sf::Vector2f pos, sf::Vector2f dir, sf::Vector2f size, float ms = 0);

        /**
         * Constructor of the Entity class.
         *
         * Initializes all the member variables with 0.
         */
        Entity();

        // Entity(const std::shared_ptr<Entity> entity);

        /**
         * Returns the position of the entity.
         *
         * \return The position of the entity as an sf::Vector2f.
         */
        sf::Vector2f getPos();

        /**
         * Returns the direction of the entity.
         *
         * \return The direction of the entity as an sf::Vector2f.
         */
        sf::Vector2f getDir();

        /**
         * Returns the x position of the entity.
         *
         * \deprecated Use `Pacenstein::Entity::getPos()` instead.
         *
         * \return A float of the x position.
         */
        [[deprecated("Use Pacenstein::Entity::getPos() instead.")]]
        float getPosX();

        /**
         * Returns the y position of the entity.
         *
         * \deprecated Use `Pacenstein::Entity::getPos()` instead.
         *
         * \return A float of the y position.
         */
        [[deprecated("Use Pacenstein::Entity::getPos() instead.")]]
        float getPosY();

        /**
         * Returns the x direction of the entity.
         *
         * \deprecated Use `Pacenstein::Entity::getDir()` instead.
         *
         * \return A float of the x direction.
         */
        [[deprecated("Use Pacenstein::Entity::getDir() instead.")]]
        float getDirX();

        /**
         * Returns the y direction of the entity.
         *
         * \deprecated Use `Pacenstein::Entity::getDir()` instead.
         *
         * \return A float of the y direction.
         */
        [[deprecated("Use Pacenstein::Entity::getDir() instead.")]]
        float getDirY();

    protected:
        // sf::RectangleShape bounding_box;
    	sf::Vector2f position, direction, size;
    	float moveSpeed;
    };
}
