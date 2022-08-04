#include "utility.h"

void update_text(const char *text, SDL_Surface **text_surface, TTF_Font *font, SDL_Color color) {
    *text_surface = TTF_RenderText_Solid(font, text, color);
    if ( ! *text_surface) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
    }
}