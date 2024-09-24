#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "settings.h"

void set_bg(map_t map, SDL_Texture* texture){
  int x, y;

  for (x = 0; x < MAP_W; x++){
    for (y = 0; y < MAP_H; y++){
      map[x][y] = (tile_t){x, y, texture};
    }
  }
}

void draw_tile(SDL_Renderer* renderer, tile_t tile, struct camera_s camera){
  float tile_screen_x;
  float tile_screen_y;
  SDL_Rect rect;

  tile_screen_x = MAP_X_TO_SCREEN(tile.x, tile.y, camera.x);
  tile_screen_y = MAP_Y_TO_SCREEN(tile.x, tile.y, camera.y);

  rect = (SDL_Rect){tile_screen_x, tile_screen_y, TILE_W, TILE_H};

  SDL_RenderCopy(renderer, tile.texture, NULL, &rect);
}

void draw_map(SDL_Renderer* renderer,map_t map, struct camera_s camera){
  int x, y;

  for (x = 0; x < MAP_W; x++){
    for (y = 0; y < MAP_H; y++){
      draw_tile(renderer, map[x][y], camera);
    }
  }
}