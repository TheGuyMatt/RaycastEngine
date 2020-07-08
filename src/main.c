#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

//player things
float px, py; //player position
void draw_player()
{
  SDL_Rect rect = {px, py, 8, 8};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
}

//map things
int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
  1,1,1,1,1,1,1,1,
  1,0,1,0,0,0,0,1,
  1,0,1,0,0,1,0,1,
  1,0,1,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,1,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};
void draw_map_2D()
{
  for (int y = 0; y < mapY; y++)
  {
    for (int x = 0; x < mapX; x++)
    {
      //set color to white if cube is there
      if (map[y * mapX + x] == 1)  { SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); }
      else { SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); }

      int xo = x * mapS, yo = y * mapS;
      SDL_Rect box = {xo, yo, mapS, mapS};
      SDL_RenderFillRect(renderer, &box);
    }
  }
}

int process_events(SDL_Event *event)
{
  while(SDL_PollEvent(event))
  {
    //return 0 if we want to quit
    if (event->type == SDL_QUIT) return 0;
    switch (event->type)
    {
      case SDL_QUIT:
        return 0;
        break;
      case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
          case SDLK_ESCAPE:
            return 0;
            break;
          case SDLK_a:
            px -= 5;
            break;
          case SDLK_d:
            px += 5;
            break;
          case SDLK_w:
            py -= 5;
            break;
          case SDLK_s:
            py += 5;
            break;
        }
        break;
    }
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
  SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
  SDL_RenderClear(renderer);

  //draw
  draw_map_2D();
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
