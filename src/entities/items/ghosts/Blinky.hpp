#pragma once

#include "../Ghost.hpp"

namespace Pacenstein {
    /**
     * The subclass for Blinky.
     *
     * Blinky is a subclass of Ghost, Blinky is the red ghost.
     *
     * Blinky is the most aggresive ghost, as he tries to make a beeline,
     * to the player immediately.
     */
    class Blinky : public Ghost {
    public:
	/**
	 * Constructor to initialize Blinky subclass.
	 */
        Blinky(){}
	
	/**
	 * Destructor to destruct Blinky subclass.
	 */
        ~Blinky(){}
    };
}
