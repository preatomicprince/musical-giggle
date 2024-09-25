#ifndef INPUT
#define INPUT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "settings.h"

struct input_s {
    int key_left;
    int key_right;
    int key_up;
    int key_down;

    int mouse_l_click;
    int mouse_r_click;
    int mouse_x;
    int mouse_y;

    bool QUIT;
};

void handle_input(SDL_Event event, struct input_s* input);
#endif