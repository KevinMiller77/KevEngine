#include "Sprite.h"
#include "PhysicsSprite.h"
#include <core/KevInput.h>

Sprite::Sprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
    type = RenderableType::Static;
}

Sprite::Sprite(float x, float y, float width, float height, Texture* inTexture)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), inTexture)
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
    // LOG_INF("Hover\n");
    if (activated)
    {
        color = 0xFFFF00FF;
        return;
    }
    color = 0xFFFFFF00;
}

void Sprite::OnMouseLeave()
{
    if (activated)
    {
        color = 0xFFFF00FF;
        return;
    }
    color = 0xFFFFFFFF;
}

void Sprite::OnClick()
{
    if (debounce.GetTimePassed() > 0.5f)
    {
        activated = !activated;
        if (type == RenderableType::Static)
        {
            type = RenderableType::Physics;
        }
        else
        {
            type = RenderableType::Static;
        }
        
        debounce.Reset();
    }
}

void Sprite::OnCollision(Renderable2D* collidedWith, bool SideDir, bool VertDir)
{
    color = 0xFFFF0000;
}

void Sprite::NoCollision()
{
    color = 0xFFFFFFFF;
}