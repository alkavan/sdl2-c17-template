#include <SDL2/SDL_image.h>
#include "utility.h"

/**
 * Creates SDL_Surface from image file
 *
 * @param surface
 * @param filename
 */
void load_image(SDL_Surface **surface, const char* const filename) {
    *surface = IMG_Load(filename);

    if(*surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to load image: %s (%s)",
                     filename, IMG_GetError());
    }
}

/**
 * Creates SDL_Surface from BMP file
 *
 * @param surface
 * @param filename
 */
void load_bitmap(SDL_Surface **surface, const char* const filename) {
    *surface = SDL_LoadBMP(filename);

    if(*surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to load bitmap: %s (%s)",
                     filename, SDL_GetError());
    }
}

/**
 * Check if double is integer (has fraction)
 *
 * @param f
 * @return
 */
bool is_fraction(double f) {
    return fmod(f, 1) == 0.0 ? false : true;
}
