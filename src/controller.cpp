#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(bool &running, Snake &snake, Snake &adversary) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          snake.ChangeDirection(Snake::Direction::kUp);
          break;

        case SDLK_DOWN:
          snake.ChangeDirection(Snake::Direction::kDown);
          break;

        case SDLK_LEFT:
          snake.ChangeDirection(Snake::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          snake.ChangeDirection(Snake::Direction::kRight);
          break;

        case SDLK_w:
          adversary.ChangeDirection(Snake::Direction::kUp);
          break;

        case SDLK_s:
          adversary.ChangeDirection(Snake::Direction::kDown);
          break;

        case SDLK_a:
          adversary.ChangeDirection(Snake::Direction::kLeft);
          break;

        case SDLK_d:
          adversary.ChangeDirection(Snake::Direction::kRight);
          break;
      }
    }
  }
}