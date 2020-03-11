#ifndef __KevEngine__
#define __KevEngine__

//Will be ifdef WIN32

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "graphics/renderables/Renderable2D.h"
#include "graphics/renderables/Sprite2D.h"
#include "graphics/renderables/Label.h"
#include "graphics/layers/Group.h"
#include "graphics/ShaderManager.h"
#include "graphics/TextureManager.h"
#include "graphics/BetterGL2DRenderer.h"

#include "utils/MemoryTracker.h"
#include "utils/Timer.h"
#include "graphics/layers/TileLayer.h"

//TODO: Move this to the input.h util
#define KEY_DEBOUNCE_TIME 0.2f

void DummyStartEngine();

struct InputInformation
{
    uint8_t _key = 0;               //If key = 0, do nothing with it
    bool _direction = 0;            //0 is down, 1 is up
    bool _previousKeyState = false; //If key was down before message sent
    uint16_t _holdCount = 0;        //How many repeats of the key were pressed
    bool _extendedKey = false;      

    Vec2u _mousePos = Vec2u(0, 0);  //New pos of mouse
    int32_t _mouseWheelMag = 0;
    int32_t _mouseWheelMagConstant = 0;
    uint32_t _mouseButtons = 0; 
};

class KevEngine
{
protected:
    std::vector<Layer*> layers;
    GLint texIDs[MAX_TEXTURE_SLOTS];

    ShaderManager shaders;
    TextureManager textures;
    FontManager fonts;
    
    bool windowedMode;
    Vec2u screenResolution;
    Vec2u mousePos;
    Vec2f screenSize;

    Timer timer;
    Timer keyPressTimeout;

    KevEngine(int screenX, int screenY)
    {
        screenResolution = Vec2u(screenX, screenY);
        mousePos = Vec2u(0, 0);
        screenSize = Vec2f(16.0f, 9.0f);
        windowedMode = true;
    }
public:

    //Runs at start of game
    virtual void OnGameStart() {};
    //Draw call obviously
    virtual void Draw() {};
    //As fast as possible
    virtual void OnTick() {};
    //60 times a second
    virtual void OnUpdate() {};
    virtual void ProcessInput(InputInformation in) {};

    inline void setScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u getScreenResolution() const { return screenResolution; }
    inline bool getWindowMode() const { return windowedMode; }
    inline void setWindowMode(bool newMode) { windowedMode = newMode; }

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u getMousePos() const { return mousePos; }

    //Callback to platform specific contect restart. Must return bool (true = success, false = fail)
    //Will be handeled in the background -- just use it
    bool (*restartContext)(); 
    //Callback to the platforma specific fullscreen toggle. Must return new windowed mode (true = windowed, false = fullscreen)
    //Will be handled in the background -- just use it
    bool (*toggleFullScreen)();  

    virtual void ResetEngine() {};
};

#endif