#ifndef __LINUX_WINDOW__
#define __LINUX_WINDOW__

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <math/math.h>

#include <utils/commonTypes.h>
#include <graphics/Window.h>
#include <graphics/GLContext.h>

#include <GLFW/glfw3.h>

struct WindowsData
{
    using EventCallbackFn = std::function<void(Event&)>;
    unsigned int width, height;
    bool windowed;
    bool VSync;
    bool callbackSet = false;
    EventCallbackFn EventCallback;
};

class LinuxWindow : public Window
{

    GLFWwindow* window;
    OpenGLContext context;
    unsigned int GLFWWinCount;
    WindowInfo info;

public:
    void ToggleFullscreen() override;

    LinuxWindow(WindowInfo inf);
    ~LinuxWindow() override;
    
    void OnUpdate() override;

    unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;

    // Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; data.callbackSet = true; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
    bool IsWindowed() const;

    void* GetNativeWindow() override { return (void*)window; }
    void* GetContext() override { return (void*)&context; }
    void SetView(int W, int H) override { context.SetView(W, H); }

    void ShutDown();
    
    static WindowsData data; 
};

#endif