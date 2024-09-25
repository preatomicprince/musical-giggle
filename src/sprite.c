#include "sprite.h"

SDL_Texture* make_texture(SDL_Renderer* renderer, const char* filepath){
    SDL_Surface* new_surface = SDL_LoadBMP(filepath);
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);
    SDL_FreeSurface(new_surface);
    return new_texture;
}

spritesheet_t* make_spritesheet(SDL_Renderer* renderer, const char* filepath, int framecount){
    SDL_Surface* new_surface;
    SDL_Texture* new_texture;
    int new_w;
    int new_h;
    spritesheet_t* new_spritesheet;
    
    new_surface = SDL_LoadBMP(filepath);

    if (new_surface == NULL){
        printf("FAILED TO LOAD BMP! \n");
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);
    new_w = new_surface->w;
    new_h = new_surface->h;

    new_spritesheet = calloc(1, sizeof(spritesheet_t));

    *new_spritesheet = (spritesheet_t){new_texture, framecount, 0, new_w, new_h};

    SDL_FreeSurface(new_surface);
    return new_spritesheet;
}

void free_spritesheet(spritesheet_t* spritesheet){
    free(spritesheet);
}

spritesheet_t* make_sprite(SDL_Renderer* renderer, const char* filepath){
  return make_spritesheet(renderer, filepath, 1);
}

int render(SDL_Renderer* renderer, spritesheet_t* spritesheet, float x, float y){
    SDL_Rect sheet_rect = {x, y, spritesheet->w, spritesheet->h};
    
    if (spritesheet->frame_count == 0){
        SDL_RenderCopy(renderer, spritesheet->texture, NULL, &sheet_rect);
    } else {
        int frame_w = spritesheet->w/spritesheet->frame_count;

        sheet_rect.w = frame_w;

        int frame_x = frame_w*spritesheet->current_frame;

        SDL_Rect frame_rect = {frame_x, 0, frame_w, sheet_rect.h};

        SDL_RenderCopy(renderer, spritesheet->texture, &frame_rect, &sheet_rect);

        int ticks = SDL_GetTicks();
        spritesheet->current_frame = (ticks/60) % spritesheet->frame_count;
    }

    return 1;
}