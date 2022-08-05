#include "utility.h"

void update_text(const char *text, SDL_Surface **text_surface, TTF_Font *font, SDL_Color color) {
    *text_surface = TTF_RenderText_Solid(font, text, color);
    if ( ! *text_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create text surface (%s)", TTF_GetError());
    }
}