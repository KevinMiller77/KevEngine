#ifndef __SPRITE_2D__
#define __SPRITE_2D__

#include <core/utils/Timer.h>
#include "Renderable2D.h"

class Sprite : public Renderable2D
{
private:
    bool activated = false;
    Timer debounce;
public:
    Sprite(float x, float y, float width, float height, const Vec4f color);
    Sprite(float x, float y, float width, float height, Texture* inTexture);

    void OnMouseHover() override;
    void OnMouseLeave() override;

    void OnCollision(Renderable2D* collidedWith) override
    {
        if (!SolidObject)   {return;}

        if (name != nullptr)
        {
            LOG_INF("%s had collision with %s", name, collidedWith->GetName());
        }
        color = 0xFFFF0000;
    }

    void NoCollision() override
    {
        if (activated)
        {
            color = 0xFFFF00FF;
            return;
        }
        //LOG_INF("Leave\n");
        color = 0xFFFFFFFF;
    }

    void OnClick()
    {
        if (debounce.GetTimePassed() > 0.5f)
        {
            activated = !activated;
            SolidObject = !SolidObject;
            debounce.Reset();
        }
    }

    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse) override
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

};

#endif