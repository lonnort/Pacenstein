#pragma once

#include <SFML/Graphics.hpp>

namespace Pacenstein {
    /**
     * The InputManager manages user inputs from keyboard and mouse.
     *
     * The player can click on menu items, or move through the maze. The InputManager makes sure
     * this bit of functionality works.
     */
    class InputManager {
    public:
        /**
         * Checks if a sprite is clicked.
         *
         * Sprites are textured SFML drawable objects - objects which can be drawn on screen. This
         * function checks if one of the sprites is clicked.
         *
         * \param object The sprite to check if it has been clicked.
         * \param button The mouse button which has been pressed.
         * \param window The window in which the mouse is present. SFML registers mouse clicks
         *               system-wide, so we have to check if the mouse is inside the window as well.
         *
         * \return A boolean true or false if the sprite has been clicked or not.
         */
        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

        /**
         * Checks if a sprite is hovered over.
         *
         * The mouse cursor changes based on the hover state. No hover: regular cursor; Yes hover:
         * clicky cursor (aka. the hand cursor with index finger raised).
         *
         * \param object The sprite over which can be hovered.
         * \param window The window in which the sprite resides.
         *
         * \return A boolean telling if the sprite is hovered or not.
         */
        bool isSpriteHovered(sf::Sprite object, sf::RenderWindow& window);

        /**
         * Get the position of the mouse relative to the window.
         *
         * 0,0 is in the top-left corner. This function is used in both `isSpriteClicked()` and
         * `isSpriteHovered()` to check if the cursor is intersecting with a sprite.
         *
         * \param window The window relative to which the mouse position has to be checked.
         *
         * \return The x and y coordinates where the pointer is pointing. This is in the format of a
         * SFML Vector2i, which is a specialization of the template `template<typename T> Vector<T>`.
         */
        sf::Vector2i getMousePosition(sf::RenderWindow& window);
    };
}
