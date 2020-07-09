#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2

#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

//player things
float px, py, pdx, pdy, pa; //player position
void draw_player()
{
  SDL_Rect rect = {px - 3, py - 3, 8, 8};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderDrawLineF(renderer, px, py, px + pdx * 5, py + pdy * 5);
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
      if (map[y * mapX + x] == 1)  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

      int xo = x * mapS, yo = y * mapS;
      SDL_Rect box = {xo + 1, yo + 1, mapS - 2, mapS - 2};
      SDL_RenderFillRect(renderer, &box);
    }
  }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
  return ( sqrt((bx-ax) * (bx-ax) + (by-ay) * (by - ay)) );
}

//draw the rays
void draw_rays_3D()
{
  int r, mx, my, mp, dof;
  float rx, ry, ra, xo, yo;

  ra = pa;
  for (r = 0; r < 1; r++)
  {
    //check horizontal
    dof = 0;
    float aTan = -1/tan(ra);
    if (ra > PI) { ry = (((int)py>>6)<<6)-0.0001; rx = (py-ry) * aTan + px; yo = -64; xo = -yo * aTan; } //looking up
    if (ra < PI) { ry = (((int)py>>6)<<6)+64;     rx = (py-ry) * aTan + px; yo = 64; xo = -yo * aTan; } //looking down
    if (ra == 0 || ra == PI) { rx = px; ry = py; dof = 8; } //looking straight left or right
    while (dof < 8)
    {
      mx = (int) (rx)>>6; my = (int) (ry)>>6; mp=my*mapX+mx;
      if (mp > 0 && mp < mapX * mapY && map[mp] == 1) dof = 8; //hit wall
      else { rx+=xo; ry+=yo; dof+= 1; } //next line
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLineF(renderer, px, py, rx, ry);

    //check vertical
    dof = 0;
    float nTan = -tan(ra);
    if (ra > P2 && ra < P3) { rx = (((int)px>>6)<<6)-0.0001; ry = (px-rx) * nTan + py; xo = -64; yo = -xo * nTan; } //looking left
    if (ra < P2 || ra > P3) { rx = (((int)px>>6)<<6)+64;     ry = (px-rx) * nTan + py; xo = 64; yo = -xo * nTan; } //looking right
    if (ra == 0 || ra == PI) { rx = px; ry = py; dof = 8; } //looking straight up or down
    while (dof < 8)
    {
      mx = (int) (rx)>>6; my = (int) (ry)>>6; mp=my*mapX+mx;
      if (mp > 0 && mp < mapX * mapY && map[mp] == 1) dof = 8; //hit wall
      else { rx+=xo; ry+=yo; dof+= 1; } //next line
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLineF(renderer, px, py, rx, ry);
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
            pa -= 0.1;
            if (pa < 0) pa += 2 * PI;
            pdx = cos(pa)*5;
            pdy = sin(pa)*5;
            break;
          case SDLK_d:
            pa += 0.1;
            if (pa > 2 * PI) pa -= 2 * PI;
            pdx = cos(pa)*5;
            pdy = sin(pa)*5;
            break;
          case SDLK_w:
            px += pdx;
            py += pdy;
            break;
          case SDLK_s:
            px -= pdx;
            py -= pdy;
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
  draw_rays_3D();
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

  px = 300; py = 300; pdx = cos(pa)*5; pdy = sin(pa)*5; //init player position
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
