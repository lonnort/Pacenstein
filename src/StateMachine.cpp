#include "StateMachine.hpp"

namespace Pacenstein {
    StateMachine::StateMachine():
        is_removing(false),
        is_adding(false),
        is_replacing(false)
    {}

    void StateMachine::addState(state_ref_t new_state, bool is_replacing) {
        this->is_adding = true;
        this->is_replacing = is_replacing;
        this->new_state = std::move(new_state);
    }

    void StateMachine::removeState() { this->is_removing = true; }

    void StateMachine::processStateChanges() {
        if (this->is_removing && !this->states.empty()) {
            this->states.pop();
            if (!this->states.empty()) this->states.top()->resume();

            this->is_removing = false;
        }
        if (this->is_adding) {
            if (!this->states.empty()) {
                if (this->is_replacing) this->states.pop();
                else this->states.top()->pause();
            }
            this->states.push(std::move(this->new_state));
            this->states.top()->init();
            this->is_adding = false;
        }
    }

    state_ref_t& StateMachine::getActiveState() { return this->states.top(); }
};
