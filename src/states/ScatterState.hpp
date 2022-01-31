#pragma once

#include <SFML/Graphics.hpp>
#include "HuntingState.hpp"
#include "Game.hpp"

namespace Pacenstein {
    /**
     * The class for the scattering state.
     *
     * The scatter state is used to create a state in which the ghosts change their behavior.
     */
    class ScatterState : public HuntingState {
    public:
        /**
         * Constructor for the ScatterState.
         *
         * \param data The pointer to GameData.
         */
        explicit ScatterState(game_data_ref_t data);

        /**
         * Initializes the scatter state variables
         *
         * Should only be called once, upon adding it to the StateMachine.
         */
        void init() override;

        /**
         * Updates the scatter state.
         *
         * \param dt The maximum time to update in the game loop.
         */
        void update(float dt) override;

    private:
        sf::Clock clock;
    };
}
