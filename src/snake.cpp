#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  if (!alive) {
    return;
  }
  auto prev_cell = HeadCell(); // We first capture the head's cell before updating.
  UpdateHead();
  auto current_cell = HeadCell();  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

SDL_Point Snake::HeadCell() const {
  SDL_Point head_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
  return head_cell;
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

bool Snake::CheckCollision(Snake const other) {

  auto head = HeadCell();

  // Check body
  for (auto const &item : other.body) {
    if (head.x == item.x && head.y == item.y) {
      alive = false;
    }
  }
  // Check head
  auto other_head = other.HeadCell();
  if (head.x == other_head.x && head.y == other_head.y) {
    alive = false;
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) const {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

Snake::Direction Snake::OppositeDirection(Snake::Direction direction) const {
  switch (direction) {
    case Direction::kUp:
      return Direction::kDown;
    case Direction::kDown:
      return Direction::kUp;
    case Direction::kRight:
      return Direction::kLeft;
    case Direction::kLeft:
      return Direction::kRight;
  }
}

void Snake::ChangeDirection(Snake::Direction newDirection) {
  if (direction != OppositeDirection(newDirection) || size == 1) {
    direction = newDirection;
  }
  return;
}

int Snake::Score() const {
  return score;
}

void Snake::IncreaseScore(unsigned int increment) {
  score += increment;
}
