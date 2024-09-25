#ifndef SPRITE
#define SPRITE

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "settings.h"

SDL_Texture* make_texture(SDL_Renderer* renderer, const char* filepath);

typedef struct spritesheet_s{
    SDL_Texture* texture;
    int frame_count;
    int current_frame;

    int w;
    int h;
}spritesheet_t;

spritesheet_t* make_spritesheet(SDL_Renderer* renderer, const char* filepath, int framecount);

spritesheet_t* make_sprite(SDL_Renderer* renderer, const char* filepath);

void free_spritesheet(spritesheet_t* spritesheet);

int render(SDL_Renderer* renderer, spritesheet_t* spritesheet, float x, float y);

#endif

