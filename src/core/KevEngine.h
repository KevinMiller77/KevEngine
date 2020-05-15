#ifndef __KevEngine__
#define __KevEngine__

//Will be ifdef WIN32
#include <core/Core.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include <graphics/renderables/Renderable2D.h>
#include <graphics/renderables/Sprite.h>
#include <graphics/renderables/Label.h>
#include <graphics/layers/Group.h>
#include <graphics/layers/Layer.h>
#include <graphics/ShaderManager.h>
#include <imgui/ImGuiLayer.h>

//#include "utils/MemoryTracker.h"
#include <utils/Timer.h>
#include <graphics/Window.h>
#include <events/Event.h>
#include <graphics/Window.h>

//TODO: Add metal here
#include <graphics/KevRenderer.h>
#include <graphics/layers/LayerStack.h>

//TODO: Move this to the input.h util
#define KEY_DEBOUNCE_TIME 0.2f

int main(int argv, char** argc);

class KevEngine
{
protected:
    Window* m_Window;
    ImGuiLayer* imGuiLayer;
    bool running = true;
    bool minimized = false;

    LayerStack EngLayerStack;
    int texIDs[16]; //Max texture slots
    
    bool windowedMode;
    Vec2u screenResolution;
    Vec2u mousePos;
    Vec2f screenSize;

    Timer timer;
    
    Timer fps;
    Timer ups;


    ShaderManager shaders;

    KevEngine* childInstance;

    void Run();
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

public:
    KevEngine(KevEngine* child);
    virtual ~KevEngine();

    static unsigned int LastFrameKeep;
    static unsigned int LastUpdateKeep;

    inline static KevEngine* Get() { return curEngine; }
    inline Window* GetWindow() { return m_Window; }

    //60 times a second
    void OnUpdate();
    void OnDraw();
    void OnEvent(Event& e);
    void OnImGuiRender();

    virtual void OnGameUpdate() {};
    virtual void OnGameDraw()  {};

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    //TODO: Reset engine
    virtual void ResetEngine() { EngineSwap(); };

    inline void SetScreenResolution(Vec2u in) { screenResolution = in; }
    inline Vec2u GetScreenResolution() const { return screenResolution; }
    inline bool GetWindowMode() const { return windowedMode; }
    inline void SetWindowMode(bool newMode) { windowedMode = newMode; }

    inline void SetMousePos(Vec2u in) { mousePos = in; }
    inline Vec2u GetMousePos() const { return mousePos; } 

private:
    static KevEngine* curEngine;
    
    static void EngineSwap();
    friend int ::main(int argv, char** argc);
};

#include <graphics/renderables/Renderable2D.h>
#endif
