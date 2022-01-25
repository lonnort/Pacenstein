#include "PowerPellet.hpp"

namespace Pacenstein {
    PowerPellet::PowerPellet(double x, double y):
        Item(x, y, 100)
    {}

    PowerPellet::PowerPellet(sf::Vector2f xy):
        PowerPellet(xy.x, xy.y)
    {}
}
