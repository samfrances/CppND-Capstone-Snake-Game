#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Got help from here: https://stackoverflow.com/questions/24534379/sdl2-alpha-not-working
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, Snake const adversary, Food const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  RenderFood(food, block);

  // render snake and adversary
  // Render bodies first, heads second, so heads always show over bodies
  RenderSnakeBody(snake, block);

  RenderSnakeBody(adversary, block);

  RenderSnakeHead(snake, block, 0x00, 0x7A, 0xCC, 0xFF);

  RenderSnakeHead(adversary, block, 0x17, 0xE3, 0x4D, 0xFF);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderFood(const Food& food, SDL_Rect& block) {
  // Render food

  // Calculate opacity based on shelf life, but with lower bound of 60
  auto opacity = std::min(
    (food.RemainingShelfLife() * 255) + 60,
    255.0f
  );

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, opacity);
  block.x = food.x() * block.w;
  block.y = food.y() * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::RenderSnakeBody(const Snake& snake, SDL_Rect& block) {

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

}

void Renderer::RenderSnakeHead(
  const Snake& snake,
  SDL_Rect& block, // TODO note use of reference
  // head colour
  Uint8 red,
  Uint8 green,
  Uint8 blue,
  Uint8 alpha
) {

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, red, green, blue, alpha);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
}


void Renderer::UpdateWindowTitle(int snakeScore, int adversaryScore, int fps) {
  std::string title{
    "Snake Score: "
    + std::to_string(snakeScore)
    + " Adversary Score: "
    + std::to_string(adversaryScore)
    + " FPS: " + std::to_string(fps)
  };
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
