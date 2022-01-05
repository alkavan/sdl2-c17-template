#ifndef SDL2_C17_UTILITY_H
#define SDL2_C17_UTILITY_H

#include <SDL2/SDL.h>

#include "types.h"

float get_elapsed_ms(Uint32 start, Uint32 end);
Uint32 get_frame_delay(Uint32 start, Uint32 end);

#endif //SDL2_C17_UTILITY_H
