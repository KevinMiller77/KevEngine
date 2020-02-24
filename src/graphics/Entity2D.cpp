#include "Entity2D.h"

Entity2D::Entity2D(const char* ID, Vec3f pos, Vec2f size, Vec4f col)
    :   UniqueID(ID), Position(pos), Size(size), Color(col) {}

Entity2D::~Entity2D() {}