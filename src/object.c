#include "object.h"

static void set_position(Object *const t, Vec2 position) {
    t->position.x = position.x;
    t->position.y = position.y;
}

static void set_rotation(Object *const t, Mat2 rotation) {
    t->rotation.m11 = rotation.m11;
    t->rotation.m12 = rotation.m12;
    t->rotation.m21 = rotation.m21;
    t->rotation.m22 = rotation.m22;
}

static void translate(Object *const t, Vec2 translation) {
    Vec2 result = svec2_add(t->position, translation);
    t->position.x = result.x;
    t->position.y = result.y;
}

static void rotate(Object *const t, float degrees) {
    Mat2 rotation = smat2_rotation_z(to_radians(degrees));
    set_rotation(t, rotation);
}

static float px(Object *const t) { return t->position.x; }

static float py(Object *const t) { return t->position.y; }

Object *object_new() {
    Object *object = (Object*) malloc(sizeof(Object));

    object->set_position = &set_position;
    object->set_rotation = &set_rotation;
    object->translate = &translate;
    object->rotate = &rotate;

    object->px = &px;
    object->py = &py;

    object->position = (Vec2){0.0f, 0.0f};
    object->rotation = smat2_rotation_z(to_radians(0));

    return object;
}

void object_free(Object *t) {
    free(t);
}
