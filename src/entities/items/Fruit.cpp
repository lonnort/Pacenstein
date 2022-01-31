#include "Fruit.hpp"

namespace Pacenstein {
    Fruit::Fruit(float x, float y, uint p):
        Item(x, y, p)
    {}

    Fruit::Fruit(sf::Vector2f xy, uint p):
        Fruit(xy.x, xy.y)
    {}

    void Fruit::interact(game_data_ref_t data) {
        data->score += points;
    }
}
