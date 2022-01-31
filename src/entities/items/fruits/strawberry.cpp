#include "strawberry.hpp"

namespace Pacenstein {
    Strawberry::Strawberry(float x, float y):
        Fruit(x, y, 300)
    {}

    Strawberry::Strawberry(sf::Vector2f xy):
        Strawberry(xy.x, xy.y)
    {}
}
