#pragma once

#include <SFML/System/Vector2.hpp>

namespace Pacenstein {
    /**
     * The class describing what anything that can be interacted with has to contain.
     *
     * Entities are items like fruits and pellets, ghosts, and the player itself.
     */
    class Entity {
    public:
        Entity(double px, double py, double sx, double sy, double dx = 0, double dy = 0, double ms = 0);
        Entity(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f dir = {0, 0}, double ms = 0);
        Entity();

        sf::FloatRect getGlobalBounds();

    protected:
        sf::RectangleShape bounding_box;

        double posX, posY;
        double dirX, dirY;
        double sizeX, sizeY;
    	double moveSpeed;
    };
}
