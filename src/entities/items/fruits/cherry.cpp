#include "cherry.hpp"

namespace Pacenstein {
    Cherry::Cherry(float x, float y):
        Fruit(x, y, 100)
    {}

    Cherry::Cherry(sf::Vector2f xy):
        Cherry(xy.x, xy.y)
    {}
}

