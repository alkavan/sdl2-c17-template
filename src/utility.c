#include <math.h>
#include <SDL2/SDL_image.h>
#include "utility.h"
#include "types.h"

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

/**
 * Convert 2d vector to radians
 *
 * @param v
 * @return
 */
double vec2_to_rad(Vec2 v) {
    return atan2(v.y, v.x);
}

/**
 * Convert 2d matrix to radians
 *
 * @param m
 * @return
 */
double mat2_to_rad(Mat2 m) {
    return atan2(m.m21, m.m22);
}

/**
 * Convert 2d vector to degrees
 *
 * @param v
 * @return
 */
double vec2_to_deg(Vec2 v) {
    return (vec2_to_rad(v) / M_PI) * 180.0;
}


/**
 * Convert 2d matrix to degrees
 *
 * @param m
 * @return
 */
double mat2_to_deg(Mat2 m) {
    return (mat2_to_rad(m) / M_PI) * 180.0;
}

Vec2 relative_mouse_position(Vec2 mouse_position, Vec2 object_position) {
    return svec2_subtract(mouse_position, object_position);
}
