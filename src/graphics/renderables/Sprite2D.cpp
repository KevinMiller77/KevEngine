#include "Sprite2D.h"

Sprite::Sprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
}