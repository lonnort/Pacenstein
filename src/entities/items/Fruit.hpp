#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * Fruits are a type of item that give bonus points.
     *
     * Fruits give bonus points and will always spawn in the center of the map. There are several
     * different fruits, ranging from strawberries to apples, each worth different amounts of
     * points. Unlike the PowerPellet, Fruit does not grant the ability to eat a Ghost.
     */
    class Fruit : public Item {};
}
