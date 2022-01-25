#include "PowerPellet.hpp"

namespace Pacenstein {
    PowerPellet::PowerPellet(float x, float y):
        Item(x, y, 100)
    {}

    PowerPellet::PowerPellet(sf::Vector2f xy):
        PowerPellet(xy.x, xy.y)
    {}
}
