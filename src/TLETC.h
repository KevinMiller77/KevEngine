#ifndef __TLETC__
#define __TLETC__

#include "graphics/renderables/StaticSprite2D.h"
#include "graphics/renderables/Sprite2D.h"
#include "graphics/BetterGL2DRenderer.h"
#include "graphics/layers/TileLayer.h"
#include "utils/Timer.h"

class TLETC
{
private:
    BetterGL2DRenderer *renderer = nullptr;
    TileLayer *layerTile = nullptr;

    Vec2u screenResolution;
    Vec2u mousePos;

    Timer timer;

public:
    TLETC(Vec2u startScreenResolution);

    void OnGameStart();
    void Draw();
    void Update();

    inline void setScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u getScreenResolution() const { return screenResolution; }

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u getMousePos() const { return mousePos; }
};

#endif