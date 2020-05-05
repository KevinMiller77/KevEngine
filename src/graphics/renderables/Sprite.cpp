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
    // LOG_INF("Hover\n");
    if (SolidObject)
    {
        if (IsName("watch"))
        {
            color = 0xFFFF00FF;
        }
        else
        {
            color = 0xFFF000FF;
        }
        return;
    }
    color = 0xFFFFFF00;
}

void Sprite::OnMouseLeave()
{
    if (SolidObject)
    {
        if (IsName("watch"))
        {
            color = 0xFFFFF000;
        }
        else
        {
            color = 0xFFFFFF00;
        }
        return;
    }
    color = 0xFFFFFFFF;
}

void Sprite::OnClick()
{
    if (debounce.GetTimePassed() > 0.5f)
    {
        if (SolidObject)
        {
            name = nullptr;
        }
        else
        {
            if (KevInput::IsMouseButtonPressed(KEV_MOUSE_BUTTON_RIGHT))
            {
                name = "watch";
            }
        }
        
        SolidObject = !SolidObject;
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

void Sprite::AddCollision(Renderable2D* collidedWith)
{
    color = 0xFFFF0000;
}

void Sprite::ProcCollision()
{
    
}

void Sprite::NoCollision()
{
    if (SolidObject)
    {
        color = 0xFFFFFF00;
        return;
    }
    color = 0xFFFFFFFF;
}
