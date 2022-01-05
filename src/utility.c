#include "utility.h"

float get_elapsed_ms(Uint32 start, Uint32 end) {
    return (float)(end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}

Uint32 get_frame_delay(Uint32 start, Uint32 end) {
    (Uint32)SDL_floorf(16.666f - get_elapsed_ms(start, end));
}
