#include "Sprite2D.h"

Sprite::Sprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
}

Sprite::Sprite(float x, float y, float width, float height, Texture* inTexture)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), Vec4f(1.0f, 1.0f, 1.0f, 1.0f))
{
    texture = inTexture;
    texID = inTexture->getTextureID();
}