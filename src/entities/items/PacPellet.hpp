#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * PacPellets are the normal point awarding currency of the game.
     *
     * Each pellet awards 10 points and does nothing special. Collect all pellets to end the game,
     * or progress to the next stage.
     */
    class PacPellet : public Item {};
}
