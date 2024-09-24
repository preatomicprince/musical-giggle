#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "settings.h"

int main() {
  SDL_Renderer* renderer = NULL;
  SDL_Window* window = NULL;
  bool RUNNING = true;

  map_t map;
  struct camera_s camera;
  camera.x = SCREEN_W/2;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Event event;

  const char* filepath = "../res/tile1.bmp";
  SDL_Surface* new_surface = SDL_LoadBMP(filepath);
  SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);

  set_bg(map, new_texture);

  while (RUNNING){
    SDL_RenderClear(renderer); //Clear screen      

    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
          RUNNING = false;
          SDL_Quit();
      }

      if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
        case SDLK_LEFT:
          camera.x += 1*CAMERA_SPEED;
          break;

        case SDLK_RIGHT:
          camera.x -= 1*CAMERA_SPEED;
          break;

        case SDLK_UP:
          camera.y += 1*CAMERA_SPEED;
          break;

        case SDLK_DOWN:
          camera.y -= 1*CAMERA_SPEED;
          break;

        case SDLK_ESCAPE:
          RUNNING = false;
          SDL_Quit();
          break;

        default:
          break;
        }
      }
    }

    draw_map(renderer, map, camera);

    SDL_RenderPresent(renderer); //Render to window
  }    
}