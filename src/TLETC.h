#include "graphics/Renderable2D.h"
#include "graphics/GL2DRenderer.h"

class TLETC
{
private:
    Renderable2D* sprites = nullptr;
    GL2DRenderer* renderer = nullptr;

    Vec2u screenSize;
    Vec2u mousePos;

public:
    TLETC(Vec2u startScreenSize);

    void OnGameStart();
    void Draw(HDC windowHDC);
    void Update();

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline void setScreenSize(Vec2u in) { screenSize = in; }
    inline Vec2u getMousePos() const { return mousePos; }
    inline Vec2u getScreenSize() const { return screenSize; }
};