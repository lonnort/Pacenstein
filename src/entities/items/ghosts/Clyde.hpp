#pragma once

#include "../Ghost.hpp"

namespace Pacenstein {
    /**
     * The subclass for Clyde.
     *
     * Clyde is a subclass of Ghost, Clyde is the orange ghost.
     *
     * Clyde is the last to leave the house. He only exists the house if a third of the pellets has been eaten.
     */

    class Clyde : public Ghost {
    public:
	/**
	 * Constructor to initialize Clyde subclass.
	 */
        Clyde(){}
	
	/**
	 * Destructor to destruct Clyde subclass.
	 */
        ~Clyde(){}
    };
}
