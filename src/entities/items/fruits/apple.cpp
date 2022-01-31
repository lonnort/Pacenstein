#include "apple.hpp"

namespace Pacenstein {
    Apple::Apple(float x, float y):
        Fruit(x, y, 700)
    {}

    Apple::Apple(sf::Vector2f xy):
        Apple(xy.x, xy.y)
    {}
}
