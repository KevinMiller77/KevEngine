#ifndef __SPRITE_2D__
#define __SPRITE_2D__

#include <utils/Timer.h>
#include <graphics/renderables/Renderable2D.h>



class Sprite : public Renderable2D
{
private:
    bool activated = false;
    Timer debounce;
public:
    Sprite(float x, float y, float width, float height, const Vec4f color);
    Sprite(float x, float y, float width, float height, Texture* inTexture);
    Sprite(Renderable2D* newMe);

    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual void OnClick() override;
    virtual void AddCollision(Renderable2D* collidedWith) override;
    virtual void ProcCollision() override;
    virtual void NoCollision() override;
};

#endif
