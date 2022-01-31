#include "grape.hpp"

namespace Pacenstein {
    Grape::Grape(float x, float y):
        Fruit(x, y, 1000)
    {}

    Grape::Grape(sf::Vector2f xy):
        Grape(xy.x, xy.y)
    {}
}
