#include "food.h"

Food::Food(int x, int y)
  : _x(x),
    _y(y),
    maxshelflife(1000) {
      shelflife = maxshelflife;
    }

Food::Food()
  : _x(0),
  _y(0),
  maxshelflife(1000) {
    shelflife = maxshelflife;
  }

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
