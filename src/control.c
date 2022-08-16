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

static void move_left(Control *const t)
{
    t->thrust.x = -BASE_THRUST;
}

static void move_right(Control *const t)
{
    t->thrust.x = BASE_THRUST;
}

static void move_forward(Control *const t)
{
    t->thrust.y = -BASE_THRUST;
}

static void move_backwards(Control *const t)
{
    t->thrust.y = BASE_THRUST;
}

static void stop_x(Control *const t)
{
    t->thrust.x = 0.0f;
}

static void stop_y(Control *const t)
{
    t->thrust.y = 0.0f;
}

static void handle(Control *const t, const SDL_KeyboardEvent *const keyboard_event) {
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
            move_left(t);
            break;
        }
        case SDLK_w: {
            move_forward(t);
            break;
        }
        case SDLK_s: {
            move_backwards(t);
            break;
        }
        case SDLK_d: {
            move_right(t);
            break;
        }
        default:
            break;
    }
}

static void update(Control *const t, const float dt, Object *const object) {
    Vec2 gravity = (Vec2){0.0f, 0.0f};

    // we begin with adding the force of gravity
    Vec2 force = svec2_multiply_f(gravity, t->mass);

    // add thrust to force vector
    force = svec2_add(force, t->thrust);

    Vec2 acceleration = (Vec2){force.x / t->mass, force.y / t->mass};

    t->velocity.x = acceleration.x * dt;
    t->velocity.y = acceleration.y * dt;

    // cap x velocity to maximum velocity
    if(t->velocity.x > MAX_VELOCITY) {
        t->velocity.x = MAX_VELOCITY;
    }

    // cap y velocity to maximum velocity
    if(t->velocity.y > MAX_VELOCITY) {
        t->velocity.y = MAX_VELOCITY;
    }

    Vec2 p = svec2_add(object->position, t->velocity);
    object->set_position(object, p);
}

Control *control_new(float mass) {
    Control *control = (Control*) malloc(sizeof(Control));

    control->handle = &handle;
    control->update = &update;
    control->set_velocity = &set_velocity;
    control->set_thrust = &set_thrust;

    control->mass = mass;
    control->velocity = (Vec2){0.0f, 0.0f};
    control->thrust = (Vec2){0.0f, 0.0f};

    return control;
}

void control_free(Control *t) {
    free(t);
}