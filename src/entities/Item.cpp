#include "Item.hpp"

namespace Pacenstein {
    Item::Item(const float x, const float y, uint p, bool collected):
        Entity({x, y}, {0, 0}, {0, 0}),
        points(p),
        collected(collected)
    {}

    Item::Item(const sf::Vector2f xy, uint p, bool collected):
        Item(xy.x, xy.y, p, collected)
    {}

    unsigned int Item::getPoints() { return this->points; }
}
