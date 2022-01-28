#pragma once

#include <SFML/Graphics.hpp>
#include "InGameState.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the hunting state.
     *
     * The HuntingState is used to create a state in which
     * specific entities change their behavior. 
     */
    class HuntingState : public InGameState {
    public:
        /**
         * Constructor to initialize HuntingState class.
         *
         * \param data A shared pointer to the game data.
         */
        explicit HuntingState(game_data_ref_t data);

        /**
         * Initializes the scatter state variables
         *
         * Should only be called once, upon adding it to the StateMachine.
         */
        void init() override {};

        /**
         * Handles input from the player.
         *
         * Reacts to the AWSD and arrow keys to move the character around.
         */
        void handleInput() override;

        /**
         * Updates the hunting state.
         *
         * Called at a certain time interval.
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt) override;
    };
}
