#ifndef SDL2_C17_UTILITY_H
#define SDL2_C17_UTILITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "types.h"

int msleep(long ms);
float get_elapsed_ms(Uint32 start, Uint32 end);
Uint32 get_frame_delay(Uint32 start, Uint32 end);
float get_fps(Uint32 start, Uint32 end);

void update_text(const char *text, SDL_Surface **text_surface, TTF_Font *font, SDL_Color color);

#endif //SDL2_C17_UTILITY_H
