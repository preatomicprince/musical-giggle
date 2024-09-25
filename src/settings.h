#ifndef SETTINGS
#define SETTINGS

typedef struct fvec2_s{
  float x, y;
}fvec2_t;

typedef struct ivec2_s{
  int x, y;
}ivec2_t;

ivec2_t fvec2_to_ivec2(fvec2_t fvec2);

// Screen width
#define SCREEN_W 700
// Screen height
#define SCREEN_H 500

#endif
