#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"

namespace Pacenstein {
    /**
     * A `std::map` containing a `std::string` and a `std::map`, which contains `std::string` times 2.
     */
    typedef std::map<std::string, std::map<std::string, std::string>> settings_t;

    /**
     * This struct stores a few major objects required for the game.
     *
     * This class is a singleton, sadly. It does make accessing these things a lot easier.
     */
    struct GameData {
        /**
         * Machine is a StateMachine, see the documentation on StateMachine for more info.
         */
        StateMachine machine;

        /**
         * Window is a SFML RenderWindow, this class is implemented by SFML.
         *
         * See [www.sfml-dev.org](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php)
         * for more information.
         */
        sf::RenderWindow window;

        /**
         * Assets is an AssetManager, see the documentation on AssetManager for more info.
         */
        AssetManager assets;

        /**
         * Input is an InputManager, see the documentation on InputManager for more info.
         */
        InputManager input;

        /**
         * Score is an unsigned int, where the score is saved when the game is running.
         */
        uint score;

        /**
         * Lives is an unsigned int, where the lives are saved when the game is running.
         */
        uint lives;

        /**
         * ghostsEaten is an unsigned int, where the number of ghosts eaten is saved when the game is running.
         */
        uint ghostsEaten;

        /**
         * scattering is a bool, where the state of scattering is saved when the game is running.
         */
        bool scattering;
        
        /**
         * Invincible is a bool, where the state of being invincible is saved when the game is running.
         */
        bool invincible;

        /**
         * pacPelletsLeft saves the number of pac pellets left for the player to collect.
         */
        uint pacPelletsLeft;

        /**
         * powerPelletsLeft saves the number of pac pellets left for the player to collect.
         */
        uint powerPelletsLeft;

        /**
         * Settings saves the settings of the game.
         */
        settings_t settings;
    };


    /**
     * This is a shared smart pointer to GameData.
     */
    typedef std::shared_ptr<GameData> game_data_ref_t;

    /**
     * This class is the main body of the game.
     *
     * The Game class loops while the window is open. While it is, it will ask the StateMachine to
     * process it's changes, ask the input handler to handle input, update the state, and draw what
     * needs to be drawn.
     */
    class Game {
    public:
        /**
         * The constructor for Game.
         *
         * This is called when you want the game to run. It will call the `create()` function of an
         * `sf::RenderWindow`, and add the SplashState to the StateMachine.
         * Then it will call the `run()` function, which starts the game.
         *
         * \param title The title for the game window.
         */
        explicit Game(const std::string& title);

    private:
        const float dt = 0.02;
        sf::Clock clock;
        game_data_ref_t data;

        void run();
        void parseSettings();
    };
}
