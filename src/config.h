#ifndef SDL2_C17_CONFIG_H
#define SDL2_C17_CONFIG_H

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;
static const int SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;
static const int SCREEN_HALF_HEIGHT = SCREEN_HEIGHT / 2;
static const int SCREEN_FPS = 60;
static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

static const int FONT_DEFAULT_SIZE = 12;
static const int FONT_DEFAULT_PADDING = 3;

static int get_line_height() {
    return FONT_DEFAULT_SIZE + FONT_DEFAULT_PADDING;
}

#endif //SDL2_C17_CONFIG_H
