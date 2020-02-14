#include "food.h"

int Food::x() const {
    return _x;
}

int Food::y() const {
    return _y;
}

bool Food::Expired() const {
    return shelflife <= 0;
}

float Food::RemainingShelfLife() const {
    if (Expired()) {
        return 0;
    }
    return shelflife / maxshelflife;
}

void Food::Update() {
    if (!Expired()) {
        shelflife -= speed;
    }
}
