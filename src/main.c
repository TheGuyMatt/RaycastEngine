#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

float px, py; //player position
void draw_player()
{
  SDL_Rect rect = {px, py, 8, 8};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int process_events(SDL_Event *event)
{
  while(SDL_PollEvent(event))
  {
    //return 0 if we want to quit
    if (event->type == SDL_QUIT) return 0;
  }

  //this makes sure the game stays running
  return 1;
}

void update()
{
}

void render(SDL_Renderer *renderer)
{
  //clear screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  //draw
  draw_player();
    
  //present
  SDL_RenderPresent(renderer);
}

void init()
{
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);

  //create sdl window
  window = SDL_CreateWindow("RaycastEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

  //create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  px = 300; py = 300; //init player position
}

int main()
{
  //initialize game
  init();

  int running = 1; 
  SDL_Event event;
  while (running)
  {
    //process events
    running = process_events(&event);

    //update the game
    update();

    //draw the game
    render(renderer);
  }

  //release resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  printf("Game shutdown\n");

  return 0;
}
