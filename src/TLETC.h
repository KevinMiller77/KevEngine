#ifndef __TLETC__
#define __TLETC__

#include <string>
#include <vector>
#include <map>
#include "graphics/renderables/Renderable2D.h"
#include "graphics/renderables/Sprite2D.h"
#include "graphics/layers/Group.h"
#include "graphics/ShaderArray.h"
#include "graphics/TextureArray.h"
#include "graphics/BetterGL2DRenderer.h"
#include "utils/Timer.h"

#include "graphics/layers/TileLayer.h"

#define NUM_TEXTURES
#define NUM_SHADERS

class TLETC
{
private:
    BetterGL2DRenderer *renderer = nullptr;
    std::vector<Layer*> layers;
    GLint texIDs[MAX_TEXTURE_SLOTS];

    ShaderArray shaders;
    TextureArray textures;

    const char** textureNames;
    const char** shaderNames;

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