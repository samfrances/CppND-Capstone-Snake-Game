#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float position_divisor)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / position_divisor),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y) const;
  void ChangeDirection(Direction newDirection);
  int Score() const;
  void IncreaseScore(unsigned int increment);
  bool CheckCollision(Snake const other);

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  Direction OppositeDirection(Direction direction) const;
  SDL_Point HeadCell() const;

  bool growing{false};
  int grid_width;
  int grid_height;
  int score{0};
  Direction direction = Direction::kUp;
};

#endif