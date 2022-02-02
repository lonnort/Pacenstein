#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Blinky.hpp"
#include "Clyde.hpp"
#include "Inky.hpp"
#include "Pinky.hpp"
#include "PacPellet.hpp"

#include "Definitions.hpp"

namespace Pacenstein {
    /**
     * The class for the in game state.
     *
     * The InGameState is used to display the current game, via raycasting.
     * It also manages the movement of the game character.
     */
    class InGameState : public State {
    public:
        /**
         * Struct containing the information needed to draw it on the screen.
         */
        struct Sprite {
            sf::Vector2f xy;
            sf::Texture tex;
        };

        /**
         * Constructor to initialize InGamestate class.
         *
         * \param data A shared pointer to the game data.
         */
        explicit InGameState(game_data_ref_t data);

        /**
         * Initializes the variables of the game state.
         *
         * Only called once, when the class is created.
         */
        void init();

        /**
         * Handles input from the player.
         *
         * Reacts to the AWSD and arrow keys to move the character around.
         *
         * \todo Only respond to a single click then transfer to hunting state
         */
        void handleInput();

        /**
         * Updates the in game state outside of key presses.
         *
         * \param dt A float.
         */
        void update(float dt);

        /**
         * Sort the sprites based on distance using combsort.
         *
         * \param &order A reference to a order vector.
         * \param &dist A reference to a vector filled with distances.
         * \param size A int with size.
         */
	void sortSprites(std::vector<int> &order, std::vector<float> &dist, int size);

        /**
         * Updates the in game state outside of key presses.
         *
         * \param dt A float.
         */
        void draw(float dt);


    protected:
    
        std::vector<PacPellet> pellets = {
                                        //   {1.5, 1.5}, {2.5, 1.5}, {3.5, 1.5}, {4.5, 1.5}, {5.5, 1.5}, {6.5, 1.5}, {7.5, 1.5}, {8.5, 1.5}, {10.5, 1.5}, {11.5, 1.5}, {12.5, 1.5}, {13.5, 1.5}, {14.5, 1.5}, {15.5, 1.5}, {16.5, 1.5}, {17.5, 1.5}, 
                                          {1.5, 2.5}, {4.5, 2.5}, {8.5, 2.5}, {10.5, 2.5}, {14.5, 2.5}, {17.5, 2.5}, 
                                        //   {1.5, 3.5}, {2.5, 3.5}, {3.5, 3.5}, {4.5, 3.5}, {5.5, 3.5}, {6.5, 3.5}, {7.5, 3.5}, {8.5, 3.5}, {9.5, 3.5}, {10.5, 3.5}, {11.5, 3.5}, {12.5, 3.5}, {13.5, 3.5}, {14.5, 3.5}, {15.5, 3.5}, {16.5, 3.5}, {17.5, 3.5}, 
                                          {1.5, 4.5}, {4.5, 4.5}, {6.5, 4.5}, {12.5, 4.5}, {14.5, 4.5}, {17.5, 4.5}, 
                                        //   {1.5, 5.5}, {2.5, 5.5}, {3.5, 5.5}, {4.5, 5.5}, {6.5, 5.5}, {7.5, 5.5}, {8.5, 5.5}, {10.5, 5.5}, {11.5, 5.5}, {12.5, 5.5}, {14.5, 5.5}, {15.5, 5.5}, {16.5, 5.5}, {17.5, 5.5}, 
                                        //   {4.5, 6.5}, {14.5, 6.5}, 
                                        //   {4.5, 7.5}, {14.5, 7.5}, 
                                        //   {4.5, 8.5}, {14.5, 8.5}, 
                                        //   {4.5, 9.5}, {14.5, 9.5}, 
                                        //   {4.5, 10.5}, {14.5, 10.5}, 
                                        //   {4.5, 11.5}, {14.5, 11.5}, 
                                        //   {4.5, 12.5}, {14.5, 12.5}, 
                                        //   {1.5, 13.5}, {2.5, 13.5}, {3.5, 13.5}, {4.5, 13.5}, {5.5, 13.5}, {6.5, 13.5}, {7.5, 13.5}, {8.5, 13.5}, {10.5, 13.5}, {11.5, 13.5}, {12.5, 13.5}, {13.5, 13.5}, {14.5, 13.5}, {15.5, 13.5}, {16.5, 13.5}, {17.5, 13.5}, 
                                        //   {1.5, 14.5}, {4.5, 14.5}, {8.5, 14.5}, {10.5, 14.5}, {14.5, 14.5}, {17.5, 14.5}, 
                                        //   {1.5, 15.5}, {2.5, 15.5}, {4.5, 15.5}, {5.5, 15.5}, {6.5, 15.5}, {7.5, 15.5}, {8.5, 15.5}, {9.5, 15.5}, {10.5, 15.5}, {11.5, 15.5}, {12.5, 15.5}, {13.5, 15.5}, {14.5, 15.5}, {16.5, 15.5}, {17.5, 15.5}, 
                                        //   {2.5, 16.5}, {4.5, 16.5}, {6.5, 16.5}, {12.5, 16.5}, {14.5, 16.5}, {16.5, 16.5}, 
                                        //   {1.5, 17.5}, {2.5, 17.5}, {3.5, 17.5}, {4.5, 17.5}, {6.5, 17.5}, {7.5, 17.5}, {8.5, 17.5}, {10.5, 17.5}, {11.5, 17.5}, {12.5, 17.5}, {14.5, 17.5}, {15.5, 17.5}, {16.5, 17.5}, {17.5, 17.5}, 
                                        //   {1.5, 18.5}, {8.5, 18.5}, {10.5, 18.5}, {17.5, 18.5}, 
                                        //   {1.5, 19.5}, {2.5, 19.5}, {3.5, 19.5}, {4.5, 19.5}, {5.5, 19.5}, {6.5, 19.5}, {7.5, 19.5}, {8.5, 19.5}, {9.5, 19.5}, {10.5, 19.5}, {11.5, 19.5}, {12.5, 19.5}, {13.5, 19.5}, {14.5, 19.5}, {15.5, 19.5}, {16.5, 19.5}, {17.5, 19.5}, 
                                          };

        game_data_ref_t data;
        Player player;

        void move(const std::string& direction);
        void generatePauseBackground();

    private:
        int w, h;

        sf::Clock clock;
        sf::Time fps;

        std::vector<int> ZBuffer;

        Blinky blinky_ghost;
        Clyde clyde_ghost;
        Inky inky_ghost;
        Pinky pinky_ghost;

        sf::Texture wallTexture;
        sf::Texture doorTexture;
        sf::Texture blinkyTexture;
        sf::Texture clydeTexture;
        sf::Texture inkyTexture;
        sf::Texture pinkyTexture;
        sf::Texture pacTexture;

        void drawWalls(map_t worldMap, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane);
        void drawEntities(std::vector<Sprite> sprites, sf::Vector2f position, sf::Vector2f direction, sf::Vector2f plane);
    };
}
