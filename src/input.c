#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input.h"

void handle_input(SDL_Event event, struct input_s* input){
  if (event.type == SDL_KEYDOWN){
      switch(event.key.keysym.sym){
          case SDLK_LEFT:
            input->key_left = 1;
            break;

          case SDLK_RIGHT:
            input->key_right = 1;
            break;

          case SDLK_UP:
            input->key_up = 1;
            break;

          case SDLK_DOWN:
            input->key_down = 1;
            break;

          case SDLK_ESCAPE:
            input->QUIT = true;
            SDL_Quit();
      }
  }else if (event.type == SDL_KEYUP){
      switch(event.key.keysym.sym){
          case SDLK_LEFT:
          input->key_left = 0;
          break;

          case SDLK_RIGHT:
          input->key_right = 0;
          break;

          case SDLK_UP:
          input->key_up = 0;
          break;

          case SDLK_DOWN:
          input->key_down = 0;
          break;
      }
  }else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEMOTION){
      SDL_GetMouseState( &input->mouse_x, &input->mouse_y);
      if (event.type == SDL_MOUSEBUTTONDOWN){
        input->mouse_l_click = 1;
      }else if(event.type == SDL_MOUSEBUTTONUP){
        input->mouse_l_click = 0;
      }
  }
}