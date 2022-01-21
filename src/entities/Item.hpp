#pragma once

#include "Entity.hpp"

namespace Pacenstein {
    /**
     * Items are entities that award points.
     */
    class Item : public Entity {
    private:
        unsigned int points;
    };
}
