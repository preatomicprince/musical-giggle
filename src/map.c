#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "settings.h"

void set_tile_texture(tile_t *tile, SDL_Texture *texture){
  tile->texture = texture;
}

void set_tile_position(tile_t *tile, int x, int y){
  tile->x = x;
  tile->y = y;
}

void set_map_tile_texture(map_t map, SDL_Texture* texture){
  int x, y;

  for (x = 0; x < MAP_W; x++){
    for (y = 0; y < MAP_H; y++){
      set_tile_position(&map[x][y], x, y);
      set_tile_texture(&map[x][y], texture);
    }
  }
}

// Sets camera offset to absolute value
void set_camera_offset(struct camera_s *camera, float x, float y){
  camera->x = x;
  camera->y = y;
}

//Change applied to camera offset from current position
void adjust_camera_offset(struct camera_s *camera, float x, float y){
  camera->x += x;
  camera->y += y;
}

void update_camera(struct camera_s *camera, struct input_s input){
  float new_x = 0.0;
  float new_y = 0.0;

  if (input.key_right){
    new_x -= CAMERA_SPEED_X;
  }
  if (input.key_left){
    new_x += CAMERA_SPEED_X;
  }
  if (input.key_up){
    new_y += CAMERA_SPEED_Y;
  }
  if (input.key_down){
    new_y -= CAMERA_SPEED_Y;
  }

  adjust_camera_offset(camera, new_x, new_y);
}

fvec2_t screen_pos_to_map_pos(float screen_x, float screen_y, struct camera_s camera){
  return (fvec2_t){SCREEN_TO_MAP_X(screen_x, screen_y, camera.x, camera.y), 
                   SCREEN_TO_MAP_Y(screen_x, screen_y, camera.x, camera.y)};
}

void draw_tile(SDL_Renderer* renderer, tile_t tile, struct camera_s camera){
  float tile_screen_x;
  float tile_screen_y;
  bool on_screen;

  tile_screen_x = MAP_TO_SCREEN_X(tile.x, tile.y, camera.x);
  tile_screen_y = MAP_TO_SCREEN_Y(tile.x, tile.y, camera.y);

  // add check for if onscreen
  on_screen = TILE_ON_SCREEN(tile_screen_x, tile_screen_y, camera.x, camera.y);

  if (!on_screen){
    return;
  }
  SDL_Rect rect;
  
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