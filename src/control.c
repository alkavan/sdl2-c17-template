#include "control.h"

void set_velocity(Control *const t, const Vec2 velocity)
{
    t->velocity.x = velocity.x;
    t->velocity.y = velocity.y;
}

void set_thrust(Control *const t, const Vec2 thrust)
{
    t->thrust.x = thrust.x;
    t->thrust.y = thrust.y;
}

void set_destination(Control *const t, const Vec2 destination)
{
    t->destination.x = destination.x;
    t->destination.y = destination.y;
}

static void move_left(Control *const t, const float dt)
{
    t->velocity.x = t->base_velocity * dt;
    t->thrust.x = -t->base_thrust * dt;
}

static void move_right(Control *const t, const float dt)
{
    t->velocity.x = t->base_velocity * dt;
    t->thrust.x = t->base_thrust * dt;
}

static void move_forward(Control *const t, const float dt)
{
    t->velocity.y = t->base_velocity * dt;
    t->thrust.y = -t->base_thrust * dt;
}

static void move_backwards(Control *const t, const float dt)
{
    t->velocity.y = t->base_velocity * dt;
    t->thrust.y = t->base_thrust * dt;
}

static void stop_x(Control *const t)
{
    t->thrust.x = 0.0f;
}

static void stop_y(Control *const t)
{
    t->thrust.y = 0.0f;
}

static void handle(Control *const t, const float dt, const SDL_KeyboardEvent *const keyboard_event) {
    // handle key up event
    if(keyboard_event->state == SDL_RELEASED) {

        switch(keyboard_event->keysym.sym)
        {
            case SDLK_d:
            case SDLK_a: {
                stop_x(t);
                break;
            }
            case SDLK_s:
            case SDLK_w: {
                stop_y(t);
                break;
            }
            default:
                break;
        }

        return;
    }

    // handle key down event
    switch(keyboard_event->keysym.sym)
    {
        case SDLK_a: {
            move_left(t, dt);
            break;
        }
        case SDLK_w: {
            move_forward(t, dt);
            break;
        }
        case SDLK_s: {
            move_backwards(t, dt);
            break;
        }
        case SDLK_d: {
            move_right(t, dt);
            break;
        }
        default:
            break;
    }
}

static void update(Control *const t, const float dt, Object *const object) {
    Vec2 v = (Vec2){
        t->thrust.x * t->velocity.x * dt,
        t->thrust.y * t->velocity.y * dt,
    };

    Vec2 p = svec2_add(object->position, v);
    object->set_position(object, p);
}

Control *control_new(float base_velocity, float base_thrust) {
    Control *control = (Control*) malloc(sizeof(Control));

    control->handle = &handle;
    control->update = &update;
    control->set_velocity = &set_velocity;
    control->set_thrust = &set_thrust;
    control->set_destination = &set_destination;

    control->base_velocity = base_velocity;
    control->base_thrust = base_thrust;
    control->velocity = (Vec2){0.0f, 0.0f};
    control->thrust = (Vec2){0.0f, 0.0f};
    control->destination = (Vec2){0.0f, 0.0f};

    return control;
}

void control_free(Control *t) {
    free(t);
}