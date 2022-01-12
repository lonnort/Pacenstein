#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace Pacenstein {
    typedef std::unique_ptr<State> state_ref_t;

    class StateMachine {
    public:
        StateMachine(){}
        ~StateMachine(){}

        void addState(state_ref_t new_state, bool is_replacing = true);
        void removeState();
        void processStateChanges();

        state_ref_t& getActiveState();

    private:
        std::stack<state_ref_t> states;
        state_ref_t new_state;
        bool is_removing;
        bool is_adding, is_replacing;
    };
}
