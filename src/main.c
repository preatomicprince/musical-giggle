#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"
#include "map.h"
#include "sprite.h"
#include "settings.h"


int main() {
  SDL_Renderer* renderer = NULL;
  SDL_Window* window = NULL;

  map_t map;
  struct camera_s camera;
  memset(&camera, 0, sizeof(camera));

  struct input_s input;
  memset(&input, 0, sizeof(input));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_Event event;

  // Loads array containing pointers to all tile textures
  // See sprite.c/.h
  load_sprites(renderer, tile_sprites, tile_sprite_filepaths, TILE_SPRITE_COUNT);

  set_map_tile_spritesheet(map, tile_sprites[dirt]);

  while (!input.QUIT){
    SDL_RenderClear(renderer); //Clear screen      

    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        input.QUIT = true;
        SDL_Quit();
      }
      handle_input(event, &input);
    }

    update_camera(&camera, input);

    draw_map(renderer, map, camera);
    draw_mouse_over_tile(renderer, map, camera, input);

    SDL_RenderPresent(renderer); //Render to window
  }
  free_sprites(tile_sprites, TILE_SPRITE_COUNT);
}