#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "settings.h"
#include "sprite.h"

void set_tile_spritesheet(tile_t *tile, spritesheet_t *spritesheet){
  tile->spritesheet = spritesheet;
}

void set_tile_position(tile_t *tile, int x, int y){
  tile->x = x;
  tile->y = y;
}

void set_map_tile_spritesheet(map_t map, spritesheet_t *spritesheet){
  int x, y;

  for (x = 0; x < MAP_W; x++){
    for (y = 0; y < MAP_H; y++){
      set_tile_position(&map[x][y], x, y);
      set_tile_spritesheet(&map[x][y], spritesheet);
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

fvec2_t map_to_screen_pos(int map_x, int map_y, struct camera_s camera){
  return (fvec2_t){
    MAP_TO_SCREEN_X(map_x, map_y, camera.x),
    MAP_TO_SCREEN_Y(map_x, map_y, camera.y)
  };
}

bool tile_on_map(int tile_x, int tile_y){
  return (tile_x >= 0 && tile_x < MAP_W) && (tile_y >= 0 && tile_y < MAP_H) ;
}


fvec2_t screen_to_map_pos(float screen_x, float screen_y, struct camera_s camera){
  return (fvec2_t){
    SCREEN_TO_MAP_X(screen_x, screen_y, camera.x, camera.y), 
    SCREEN_TO_MAP_Y(screen_x, screen_y, camera.x, camera.y)
    };
}

void draw_tile_outline(SDL_Renderer *renderer, map_t map, int tile_index_x, int tile_index_y, struct camera_s camera){
  fvec2_t  tile_screen_pos;
  SDL_Point line_points[5];

  // Return if not on map
  if (!tile_on_map(tile_index_x, tile_index_y)){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return;
  }

  tile_screen_pos = map_to_screen_pos(tile_index_x, tile_index_y, camera);

  line_points[0] = (SDL_Point){tile_screen_pos.x + HALF_TILE_W, tile_screen_pos.y};
  line_points[1] = (SDL_Point){tile_screen_pos.x + TILE_W,      tile_screen_pos.y + HALF_TILE_H};
  line_points[2] = (SDL_Point){tile_screen_pos.x + HALF_TILE_W, tile_screen_pos.y + TILE_H};
  line_points[3] = (SDL_Point){tile_screen_pos.x,               tile_screen_pos.y + HALF_TILE_H};
  line_points[4] = line_points[0];
  
  SDL_RenderDrawLines(renderer, line_points, 5);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void draw_mouse_over_tile(SDL_Renderer *renderer, map_t map, struct camera_s camera, struct input_s input){
  fvec2_t mouse_map_pos_f;
  ivec2_t mouse_map_pos_i;

  mouse_map_pos_f = screen_to_map_pos(input.mouse_x, input.mouse_y, camera);
  mouse_map_pos_i = fvec2_to_ivec2(mouse_map_pos_f);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
  draw_tile_outline(renderer, map, mouse_map_pos_i.x, mouse_map_pos_i.y, camera);
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

  render(renderer, tile.spritesheet, tile_screen_x, tile_screen_y);
}

void draw_map(SDL_Renderer* renderer,map_t map, struct camera_s camera){
  int x, y;

  for (x = 0; x < MAP_W; x++){
    for (y = 0; y < MAP_H; y++){
      draw_tile(renderer, map[x][y], camera);
    }
  }
}