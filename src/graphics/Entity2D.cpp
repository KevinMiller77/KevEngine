#include "Entity2D.h"

Entity2D::Entity2D(const char* ID, Vec3 pos, Vec2 size, Vec4 col)
    :   UniqueID(ID), Position(pos), Size(size), Color(col) {}

Entity2D::~Entity2D() {}