#pragma once

#include "../Entity.hpp"

namespace Pacenstein {
    class Item : Entity {
    public:
        Item(){}
        ~Item(){}
    private:
        unsigned int points;
    };
}
