#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"

class Food {
 public:

  Food(int x, int y);
  Food();

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