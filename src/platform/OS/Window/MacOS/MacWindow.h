#ifndef __MAC_WINDOW__
#define __MAC_WINDOW__

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <math/math.h>

#include <utils/commonTypes.h>
#include <graphics/Window.h>

#include <core/Core.h>
#include <core/KevEngine.h>
#include <math/math.h>

#ifdef KEV_RENDERAPI_METAL
    #define GLFW_INCLUDE_NONE
    #define GLFW_EXPOSE_NATIVE_COCOA
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>
    #import <Metal/Metal.h>
    #import <QuartzCore/QuartzCore.h>
#endif

#include <platform/graphics/Metal/renderer/MetalContext.h>

class GLFWWindow;

struct MacData
{
    using EventCallbackFn = std::function<void(Event&)>;
    unsigned int width, height;
    int w_width, w_height;
    int windowed_x, windowed_y;
    bool windowed;
    bool VSync;
    bool callbackSet = false;
    EventCallbackFn EventCallback;
};

class MacWindow : public Window
{

    GLFWwindow* window;
    
    MetalContextLayer* m_Context;
    Vec2u viewportSize;
    unsigned int GLFWWinCount;
    WindowInfo info;
    id <MTLDevice> device;
    id <MTLCommandQueue> queue;

    int InitalizeConsole();

public:

    inline bool IsWindowed() override { return data.windowed; }
    void ToggleFullscreen() override;
    virtual void CallWindowHints() override;

    MacWindow(WindowInfo inf);
    ~MacWindow();
    
    void Init();
    void OnUpdate() override;
    
    unsigned int* GetWidthPtr() const override;
    unsigned int* GetHeightPtr() const override;

    unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;

    // Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; data.callbackSet = true; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

    void* GetNativeWindow() override { return (void*)window; }
    void* GetContext() override { return (void*)m_Context; }
    void SetView(int W, int H) override { m_Context->SetView(W, H); }

    void ShutDown();
    
    inline id <MTLDevice> GetDevice() { return device; }
    inline id <MTLCommandQueue> GetQueue() { return queue; }
    inline CAMetalLayer* GetLayer() { return m_Context->GetIntLayer(); }
    
    static MacData data; 
};

#endif
