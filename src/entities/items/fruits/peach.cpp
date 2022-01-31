#include "peach.hpp"

namespace Pacenstein {
    Peach::Peach(float x, float y):
        Fruit(x, y, 500)
    {}

    Peach::Peach(sf::Vector2f xy):
        Peach(xy.x, xy.y)
    {}
}
