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
    // LOG_INF("Hover\n");
    if (KevInput::IsMouseButtonPressed(KEV_MOUSE_BUTTON_LEFT))
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

void Sprite::OnClick()
{
    if (debounce.GetTimePassed() > 0.5f)
    {
        activated = !activated;
        SolidObject = !SolidObject;
        debounce.Reset();
    }
}

void Sprite::MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse)
{
    if ((mousePos.x > GetScreenPos().x && mousePos.x < GetScreenPos().x + size.x) && (mousePos.y > GetScreenPos().y && mousePos.y < GetScreenPos().y + size.y))
    {
        if (underMouse.size() == 0)
        {
            OnMouseHover();
            mouseHovering = true;
        } else if (mouseHovering)
        {
            OnMouseLeave();
            mouseHovering = false;
        }

        underMouse.push_back(this);
    }

    else if (mouseHovering)
    {
        OnMouseLeave();
        mouseHovering = false;
    }

}

void Sprite::OnCollision(Renderable2D* collidedWith)
{
    if (!SolidObject)   {return;}

    if (name != nullptr)
    {
        LOG_INF("%s had collision with %s", name, collidedWith->GetName());
    }
    color = 0xFFFF0000;
}

void Sprite::NoCollision()
{
    if (activated)
    {
        color = 0xFFFF00FF;
        return;
    }
    //LOG_INF("Leave\n");
    color = 0xFFFFFFFF;
}