#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"

class Food {
 public:

  Food(int x, int y)
      : _x(x),
        _y(y) {}

  Food() : _x(0), _y(0) {}

  void Update();
  int x() const;
  int y() const;

 private:
  int _x;
  int _y;
  float speed{0.1f};
};

#endif