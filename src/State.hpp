#pragma once

namespace Pacenstein {
    /**
     * States are what state the game can be in.
     *
     * The game can be in a menu, in-game (currently playing), and more.
     *
     * This is a pure virtual class.
     */
    class State {
    public:
        virtual void init       () = 0;
        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void draw  (float dt) = 0;

        virtual void pause (){};
        virtual void resume(){};
    };
}
