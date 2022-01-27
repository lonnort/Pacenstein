#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace Pacenstein {
    typedef std::unique_ptr<State> state_ref_t;

    /**
     * The StateMachine manages the states, changes the currently active state and remove inactive
     * states.
     */
    class StateMachine {
    public:
        StateMachine();

        /**
         * Call this to change to a new state.
         *
         * This adds a State to the stack owned by this class. It is possible to replace the
         * currently active state by setting `is_replacing` to `true`. Adding a state makes it
         * active.
         *
         * \param new_state    A pointer to a state which has to be added.
         * \param is_replacing Set to true if you want the state to replace the last, set to false
         *                     if you want to keep the previous state. This is useful if you want to
         *                     go back to the previous state.
         */
        void addState(state_ref_t new_state, bool is_replacing = true);

        /**
         * Call this to change to a previous state or to crash the game.
         *
         * This removes the last added state from the stack, reverting the active state back to the
         * state before it. ex: the stack contains MainMenuState and InGameState. You remove
         * InGameState. Now we're back in the main menu.
         */
        void removeState();

        /**
         * Call this to actually process the changes made with `addState()` and `removeState()`.
         */
        void processStateChanges();

        /**
         * The active state is the State on top of the stack.
         *
         * \return The pointer to the active state.
         */
        state_ref_t& getActiveState();

    private:
        std::stack<state_ref_t> states;
        state_ref_t new_state;
        bool is_removing, is_adding, is_replacing;
    };
}
