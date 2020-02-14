#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"

class Food {
 public:

  Food(int x, int y)
      : _x(x),
        _y(y),
        maxshelflife(1000) {
          shelflife = maxshelflife;
        }

  Food()
      : _x(0),
      _y(0),
      maxshelflife(1000) {
        shelflife = maxshelflife;
      }

  void Update();
  int x() const;
  int y() const;
  bool Expired() const;
  float RemainingShelfLife() const;

 private:
  int _x;
  int _y;
  float speed{3};
  float shelflife;
  float maxshelflife;
};

#endif