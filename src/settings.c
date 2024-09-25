#include "settings.h"

ivec2_t fvec2_to_ivec2(fvec2_t fvec2){
  return (ivec2_t){
    (int)fvec2.x,
    (int)fvec2.y
  };
}