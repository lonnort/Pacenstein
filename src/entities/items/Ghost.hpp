#pragma once

#include "Item.hpp"

namespace Pacenstein {
    /**
     * Ghosts are item that move around on their own volition.
     *
     * Every ghost has a different AI for attacking the Player. Every ghost is capable of deducting
     * a life from the player, unless the player has eaten a PowerPellet, then the ghosts will
     * scatter and flee from the player. If the player were to eat a ghost in this state points are
     * awarded based on how many ghosts were eaten: 200 for the first, then 400, 800, and 1600 last.
     */
    class Ghost : public Item {};
}
