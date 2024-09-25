#ifndef SPRITE
#define SPRITE

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"

typedef struct spritesheet_s{
    SDL_Texture* texture;
    int frame_count;
    int current_frame;

    int w;
    int h;
}spritesheet_t;

//
// Dirt texture 
//

// NUM must be last in list
enum tile_sprites_e{
    dirt = 0,
    blue,
    NUM_TILE_SPRITES
};
#define TILE_SPRITE_COUNT NUM_TILE_SPRITES
extern spritesheet_t *tile_sprites[];
extern const char *tile_sprite_filepaths[];

SDL_Texture* make_texture(SDL_Renderer* renderer, const char* filepath);

spritesheet_t* make_spritesheet(SDL_Renderer* renderer, const char* filepath, int framecount);

spritesheet_t* make_sprite(SDL_Renderer* renderer, const char* filepath);

void free_spritesheet(spritesheet_t* spritesheet);

int render(SDL_Renderer* renderer, spritesheet_t* spritesheet, float x, float y);

void load_sprites(SDL_Renderer *renderer, spritesheet_t **sprite_list, const char **filepath_list, int sprite_count);

void free_sprites(spritesheet_t **sprite_list, int sprite_count);
#endif