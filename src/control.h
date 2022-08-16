#ifndef SDL2_C17_CONTROL_H
#define SDL2_C17_CONTROL_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "object.h"
#include "types.h"

#define MAX_VELOCITY 10.0f
#define BASE_THRUST 100.0f

struct Control {
    struct {
        void (*handle)(struct Control *const, const SDL_KeyboardEvent *const keyboard_event);
        void (*update)(struct Control *const, const float dt, Object *const object);
        void (*set_velocity)(struct Control *const, const Vec2 velocity);
        void (*set_thrust)(struct Control *const, const Vec2 thrust);
    };

    float mass;

    Vec2 velocity;
    Vec2 thrust;
};

typedef struct Control Control;

Control *control_new(float mass);
void control_free(Control *t);

#endif //SDL2_C17_CONTROL_H
