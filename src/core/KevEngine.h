#ifndef __KevEngine__
#define __KevEngine__

//Will be ifdef WIN32
#include <core/Core.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "graphics/renderables/Renderable2D.h"
#include "graphics/renderables/Sprite2D.h"
#include "graphics/renderables/Label.h"
#include "graphics/layers/Group.h"
#include "graphics/layers/Layer.h"
#include "graphics/ShaderManager.h"
#include "graphics/BetterGL2DRenderer.h"

//#include "utils/MemoryTracker.h"
#include "utils/Timer.h"
#include "graphics/Window.h"
#include "events/Event.h"

//TODO: Move this to the input.h util
#define KEY_DEBOUNCE_TIME 0.2f

#ifdef KEV_PLATFORM_WINDOWS
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
#else
    int main(int argv, char** argc);
#endif
class KevEngine
{
protected:
    std::unique_ptr<Window> window;
    bool running = true;
    bool minimized = false;

    std::vector<Layer*> layers;
    GLint texIDs[MAX_TEXTURE_SLOTS];
    
    bool windowedMode;
    Vec2u screenResolution;
    Vec2u mousePos;
    Vec2f screenSize;

    Timer timer;

    ShaderManager shaders;

    KevEngine* childInstance;

    void Run();
    bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

public:
    KevEngine(KevEngine* child);
    virtual ~KevEngine() {}

    //60 times a second
    void OnUpdate();
    void OnDraw();
    void OnEvent(Event& e);

    virtual void OnChildUpdate() {};
    virtual void OnChildDraw()  {};

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    //TODO: Reset engine
    virtual void ResetEngine() {};

    inline void setScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u getScreenResolution() const { return screenResolution; }
    inline bool getWindowMode() const { return windowedMode; }
    inline void setWindowMode(bool newMode) { windowedMode = newMode; }

    inline void setMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u getMousePos() const { return mousePos; } 

private:
    static KevEngine* curEngine;
#ifdef KEV_PLATFORM_WINDOWS
#include <windef.h>
    friend int ::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
#else
    friend int ::main(int argv, char** argc);
#endif
};

#endif