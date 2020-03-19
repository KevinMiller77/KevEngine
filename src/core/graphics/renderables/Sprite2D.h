#ifndef __SPRITE_2D__
#define __SPRITE_2D__

#include <core/Input.h>
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

    void OnMouseHover() override
    {
        //LOG_INF("Hover\n");
        if (Input::IsKeyPressed(KEV_MOUSE_BUTTON_LEFT))
        {
            OnClick();
        }
        color = 0xFFFFFF00;
    }

    void OnMouseLeave() override
    {
        if (activated)
        {
            color = 0xFFFF00FF;
            return;
        }
        //LOG_INF("Leave\n");
        color = 0xFFFFFFFF;
    }

    void OnCollision(Renderable2D* collidedWith) override
    {
        if (!SolidObject)   {return;}

        color = 0xFFFF0000;
    }

    void NoCollision() override
    {
        color = 0xFFFFFFFF;
    }

    void OnClick()
    {
        if (debounce.getTimePassed() > 0.5f)
        {
            activated = !activated;
            debounce.reset();
        }
    }

};

#endif