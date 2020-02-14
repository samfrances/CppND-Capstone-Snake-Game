#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, 3),
      adversary(grid_width, grid_height, 1.6666),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, adversary);
    Update();
    renderer.Render(snake, adversary, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(snake.Score(), adversary.Score(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !adversary.SnakeCell(x, y)) {
      food = Food{x, y};
      return;
    }
  }
}

bool Game::GameOver() const {
  return !snake.alive && !adversary.alive;
}

void Game::Update() {
  if (GameOver()) return;

  UpdatePlayer(snake);
  UpdatePlayer(adversary);

  snake.CheckCollision(adversary);
  adversary.CheckCollision(snake);

}

void Game::UpdatePlayer(Snake& theSnake) {
  theSnake.Update();

  int new_x = static_cast<int>(theSnake.head_x);
  int new_y = static_cast<int>(theSnake.head_y);

  // Check if there's food over here
  if (food.x() == new_x && food.y() == new_y) {
    theSnake.IncreaseScore(1);
    PlaceFood();
    // Grow snake and increase speed.
    theSnake.GrowBody();
    theSnake.speed += 0.02;
  }

}

int Game::SnakeScore() const { return snake.Score(); }
int Game::SnakeSize() const { return snake.size; }
int Game::AdversaryScore() const { return adversary.Score(); }
int Game::AdversarySize() const { return adversary.size; }