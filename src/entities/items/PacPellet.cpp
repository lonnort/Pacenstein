#include "PacPellet.hpp"

namespace Pacenstein {
    PacPellet::PacPellet(double x, double y):
        Item(x, y, 10)
    {}

    PacPellet::PacPellet(sf::Vector2f xy):
        PacPellet(xy.x, xy.y)
    {}
}
