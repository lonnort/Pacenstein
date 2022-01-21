#pragma once

#include <SFML/System/Vector2.hpp>

#include "Entity.hpp"

namespace Pacenstein {
    /**
     * The player is an entity that moves around in the map according to the user's input.
     *
     * Might end up unused.
     */
    class Player : public Entity {
    private:
    	// score Score;
    	unsigned int lives;
    };
}
