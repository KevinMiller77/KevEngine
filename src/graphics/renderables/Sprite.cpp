#include "Sprite.h"
#include "PhysicsSprite.h"
#include <core/KevInput.h>

Sprite::Sprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
    type = RenderableType::Static;
}

Sprite::Sprite(float x, float y, float width, float height, Texture* inTexture, Vec2u TilesheetPos)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), inTexture, TilesheetPos)
{
    type = RenderableType::Static;
}

Sprite::Sprite(Renderable2D* newMe)
    : Renderable2D(newMe)
{
    type = RenderableType::Static;
}

void Sprite::OnMouseHover()
{
}

void Sprite::OnMouseLeave()
{
}

void Sprite::OnClick()
{
}

void Sprite::AddCollision(Renderable2D* collidedWith)
{
}

void Sprite::ProcCollision()
{
    
}

void Sprite::NoCollision()
{
    
}
