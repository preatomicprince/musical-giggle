#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"
#include "map.h"
#include "settings.h"


int main() {
  SDL_Renderer* renderer = NULL;
  SDL_Window* window = NULL;

  map_t map;
  struct camera_s camera;

  struct input_s input;
  memset(&input, 0, sizeof(input));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Event event;

  const char* filepath = "../res/tile1.bmp";
  SDL_Surface* new_surface = SDL_LoadBMP(filepath);
  SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);

  set_bg(map, new_texture);

  while (!input.QUIT){
    SDL_RenderClear(renderer); //Clear screen      

    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
          SDL_Quit();
      }
      handle_input(event, &input);
    }

    update_camera(&camera, input);

    draw_map(renderer, map, camera);

    SDL_RenderPresent(renderer); //Render to window
  }    
}