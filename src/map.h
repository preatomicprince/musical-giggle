#ifndef MAP
#define MAP

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"
#include "input.h"


#define TILE_W 222
#define TILE_H 128
#define HALF_TILE_W TILE_W/2
#define HALF_TILE_H TILE_H/2

#define ISOMETRIC_RATIO TILE_W/TILE_H 


// Number of tiles in map's x and y
#define MAP_W 16
#define MAP_H 16


typedef struct  tile_s{
    
  // X and Y index in map
  int x;
  int y;

  SDL_Texture *texture;

  // List of pointers to entities on tile
  // to-do: Add entities
  // entities *entities;
}tile_t;

// Array holding all tiles that make up map
typedef tile_t map_t[MAP_W][MAP_H];

void set_tile_texture(tile_t *tile, SDL_Texture *texture);

void set_tile_position(tile_t *tile, int x, int y);

void set_map_tile_texture(map_t map, SDL_Texture* texture);

#define CAMERA_SPEED 0.5
#define CAMERA_SPEED_X CAMERA_SPEED*ISOMETRIC_RATIO
#define CAMERA_SPEED_Y CAMERA_SPEED

// Contains data of what is displayed on screen
struct camera_s{
  // Map offset
  float x, y;
  int min_x_offset, max_x_offset, min_y_offset, max_y_offset;
};

void set_camera_offset(struct camera_s *camera, float x, float y);

void adjust_camera_offset(struct camera_s *camera, float x, float y);

void update_camera(struct camera_s *camera, struct input_s input);

// Get screen position from map to where it appears on screen
#define MAP_TO_SCREEN_X(map_x, map_y, camera_x) ((map_x - map_y)*HALF_TILE_W + camera_x)
#define MAP_TO_SCREEN_Y(map_x, map_y, camera_y) ((map_x + map_y)*HALF_TILE_H + camera_y)

fvec2_t map_to_screen_pos(int map_x, int map_y, struct camera_s camera);

// Return true if on screen
#define X_ON_SCREEN(screen_x, camera_x) ((screen_x > 0 - TILE_W) && (screen_x < SCREEN_W + TILE_W))
#define Y_ON_SCREEN(screen_y, camera_y) ((screen_y > 0 - TILE_H) && (screen_y < SCREEN_H + TILE_H))
#define TILE_ON_SCREEN(screen_x, screen_y, camera_x, camera_y) (X_ON_SCREEN(screen_x, camera_x) && Y_ON_SCREEN(screen_y, camera_y))

bool tile_on_map(int tile_x, int tile_y);

#define SCREEN_TO_MAP_X(screen_x, screen_y, camera_x, camera_y) ((2*(screen_x-camera_x)/HALF_TILE_W) + (2*(screen_y - camera_y)/HALF_TILE_H) - 0.5)
#define SCREEN_TO_MAP_Y(screen_x, screen_y, camera_x, camera_y) ((2*(screen_y - camera_y)/HALF_TILE_H) - (2*(screen_x - camera_x)/HALF_TILE_W) + 0.5)

fvec2_t screen_to_map_pos(float screen_x, float screen_y, struct camera_s camera);

void draw_tile_outline(SDL_Renderer *renderer, map_t map, int tile_index_x, int tile_index_y, struct camera_s camera);

void draw_mouse_over_tile(SDL_Renderer *renderer, map_t map, struct camera_s camera, struct input_s input);

void draw_tile(SDL_Renderer* renderer, tile_t tile, struct camera_s camera);

void draw_map(SDL_Renderer* renderer,map_t map, struct camera_s camera);

#endif