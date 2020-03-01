#ifndef __TLETC__
#define __TLETC__

#include "graphics/renderables/StaticSprite2D.h"
#include "graphics/GL2DRenderer.h"

class TLETC
{
private:
    Renderable2D *sprites = nullptr;
    GL2DRenderer *renderer = nullptr;

    Vec2u screenResolution;
    Vec2u mousePos;

public:
    TLETC(Vec2u startScreenResolution);

    void OnGameStart();
    void Draw(HDC windowHDC);
    void Update();

    inline void setScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u getScreenResolution() const { return screenResolution; }

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u getMousePos() const { return mousePos; }
};

#endif