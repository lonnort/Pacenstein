#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the splash state.
     *
     * The splash state is used to load assets and not much more. It pretty much only calls
     * something like `loadSomeAsset()` on the AssetManager, and displays an image while doing it.
     */
    class SplashState : public State {
    public:
        /**
         * The constructor for splash state.
         *
         * \param data The pointer to GameData. This contains the all important AssetManager.
         */
        explicit SplashState(game_data_ref_t data);

        /**
         * Initializes pause state variables and screen objects.
         *
         * Should only be called upon adding this state to the StateMachine.
         */
        void init();

        /**
         * Handles input from the user.
         *
         * In this case it only listens to the "close-the-window" button.
         */
        void handleInput();

        /**
         * Update the splash state.
         *
         * In this case it forces the splash state to continue to the MainMenuState after a few
         * seconds. We don't have enough assets to really need a loading screen, but hey, it do be
         * looking fancy tho.
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt);

        /**
         * Draws the screen objects on screen.
         *
         * \param dt The maximum time to draw in the game loop.
         */
        void draw(float dt);

    private:
        game_data_ref_t data;
        sf::Clock clock;
        sf::Sprite background;

        void loadAssets();
    };
}
