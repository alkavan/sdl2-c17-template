#ifndef SDL2_C17_CONTROL_H
#define SDL2_C17_CONTROL_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "object.h"
#include "types.h"

struct Control {
    struct {
        void (*handle)(struct Control *const, const float dt, const SDL_KeyboardEvent *const keyboard_event);
        void (*update)(struct Control *const, const float dt, Object *const object);
        void (*set_velocity)(struct Control *const, const Vec2 velocity);
        void (*set_thrust)(struct Control *const, const Vec2 thrust);
        void (*set_destination)(struct Control *const, const Vec2 destination);
    };

    float base_velocity;
    float base_thrust;

    Vec2 velocity;
    Vec2 thrust;
    Vec2 destination;
};

typedef struct Control Control;

Control *control_new(float base_velocity, float base_thrust);
void control_free(Control *t);

#endif //SDL2_C17_CONTROL_H
