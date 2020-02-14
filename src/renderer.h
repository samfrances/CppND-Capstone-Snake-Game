#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, Snake const adversary, Food const &food);
  void UpdateWindowTitle(int snakeScore, int adversaryScore, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void RenderSnakeBody(
    Snake const snake,
    SDL_Rect& block
  );

  void RenderSnakeHead(
    Snake const snake,
    SDL_Rect& block,
    Uint8 red,
    Uint8 green,
    Uint8 blue,
    Uint8 alpha
  );
};

#endif