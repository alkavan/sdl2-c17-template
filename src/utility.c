#include <time.h>
#include <errno.h>

#include "utility.h"

int msleep(long ms)
{
    struct timespec ts;
    int res;

    if (ms < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

float get_elapsed_ms(Uint32 start, Uint32 end) {
    return (float)(end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}

Uint32 get_frame_delay(Uint32 start, Uint32 end) {
    (Uint32)SDL_floor(16.666f - get_elapsed_ms(start, end));
}

float get_fps(Uint32 start, Uint32 end) {
    float elapsed = (float)(end - start) / (float)SDL_GetPerformanceFrequency();
    return 1.0f / elapsed;
}

void update_text(const char *text, SDL_Surface **text_surface, TTF_Font *font, SDL_Color color) {
    *text_surface = TTF_RenderText_Solid(font, text, color);
    if ( ! *text_surface) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
    }
}