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
    Sprite(float x, float y, float width, float height, unsigned int inTexture);

    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual void OnCollision(Renderable2D* collidedWith) override;
    virtual void NoCollision() override;
    virtual void OnClick() override;
    virtual void MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse) override;

};

#endif