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

struct InputInformation
{
    uint8_t _key = 0;               //If key = 0, do nothing with it
    bool _direction = 0;            //0 is down, 1 is up
    bool _previousKeyState = false; //If key was down before message sent
    uint16_t _holdCount = 0;        //How many repeats of the key were pressed
    bool _extendedKey = false;      

    Vec2u _mousePos = Vec2u(0, 0);  //New pos of mouse
};

class TLETC
{
private:
    std::vector<Layer*> layers;
    GLint texIDs[MAX_TEXTURE_SLOTS];

    ShaderArray shaders;
    TextureArray textures;

    Vec2u screenResolution;
    Vec2u mousePos;

    Timer timer;
    Timer keyPressTimeout;

public:
    TLETC(Vec2u startScreenResolution);

    void OnGameStart();
    void Draw();
    void Update();
    void ProcessInput(InputInformation in);

    inline void setScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u getScreenResolution() const { return screenResolution; }

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u getMousePos() const { return mousePos; }

    bool (*restartContext)();  //Callback to the platforma specific restartContext function

    void ResetEngine();
private:
};

#endif