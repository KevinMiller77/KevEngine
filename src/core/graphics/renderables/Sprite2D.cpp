#include "Sprite2D.h"
#include <core/KevInput.h>

Sprite::Sprite(float x, float y, float width, float height, const Vec4f color)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), color)
{
}

Sprite::Sprite(float x, float y, float width, float height, Texture* inTexture)
    : Renderable2D(Vec3f(x, y, 0), Vec2f(width, height), Vec4f(1.0f, 1.0f, 1.0f, 1.0f))
{
    texture = inTexture;
    texID = inTexture->GetTexID();
}

void Sprite::OnMouseHover()
{
    //LOG_INF("Hover\n");
    if (KevInput::IsKeyPressed(KEV_MOUSE_BUTTON_LEFT))
    {
        OnClick();
    }
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
    //LOG_INF("Leave\n");
    color = 0xFFFFFFFF;
}