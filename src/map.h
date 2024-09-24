#ifndef MAP
#define MAP

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"

#define TILE_W 128
#define TILE_H 64
#define HALF_TILE_W TILE_W/2
#define HALF_TILE_H TILE_H/2

// Number of tiles in map's x and y
#define MAP_W 32
#define MAP_H 32

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

void set_bg(map_t map, SDL_Texture* texture);

#define CAMERA_SPEED 10

// Contains data of what is displayed on screen
struct camera_s{
  // Map offset
  float x, y;
};

// Get screen position from map to where it appears on screen
#define MAP_X_TO_SCREEN(map_x, map_y, camera_x) ((map_x - map_y)*HALF_TILE_W - HALF_TILE_W + camera_x)
#define MAP_Y_TO_SCREEN(map_x, map_y, camera_y) ((map_x + map_y)*HALF_TILE_H + camera_y)

// Return true if on screen
#define X_ON_SCREEN(screen_x, camera_x) ((screen_x > 0 + camera.x - TILE_W) && (screen_x < SCREEN_W + camera.x + TILE_W))
#define Y_ON_SCREEN(screen_y, camera_y) ((screen_y > 0 + camera.y - TILE_H) && (screen_y < SCREEN_H + camera.y + TILE_H))
#define TILE_ON_SCREEN(screen_x, screen_y, camera_x, camera_y) (X_ON_SCREEN && Y_ON_SCREEN)

/* 
// Return pointer to list of entities
entity** get_entities_on_tile (tile_t* map, int x, int y);
*/

void draw_tile(SDL_Renderer* renderer, tile_t tile, struct camera_s camera);

void draw_map(SDL_Renderer* renderer,map_t map, struct camera_s camera);

#endif