#include "object.h"

static void set_position(Object *const t, Vec2 position) {
    t->position.x = position.x;
    t->position.y = position.y;
}

static void set_rotation(Object *const t, Vec2 rotation) {
    t->rotation.x = rotation.x;
    t->rotation.y = rotation.y;
}

static void translate(Object *const t, Vec2 translation) {
    Vec2 result = svec2_add(t->position, translation);
    t->position.x = result.x;
    t->position.y = result.y;
}

static void rotate(Object *const t, Vec2 rotation) {
    Vec2 result = svec2_add(t->rotation, rotation);
    t->rotation.x = result.x;
    t->rotation.y = result.y;
}

static float px(Object *const t) { return t->position.x; }

static float py(Object *const t) { return t->position.y; }

static float rx(Object *const t) { return t->rotation.x; }

static float ry(Object *const t) { return t->rotation.y; }

Object *object_new() {
    Object *object = (Object*) malloc(sizeof(Object));

    object->set_position = &set_position;
    object->set_rotation = &set_rotation;
    object->translate = &translate;
    object->rotate = &rotate;

    object->px = &px;
    object->py = &py;

    object->rx = &rx;
    object->ry = &ry;

    object->position = (Vec2){0.0f, 0.0f};
    object->rotation = (Vec2){0.0f, 0.0f};

    return object;
}

void object_free(Object *t) {
    free(t);
}
