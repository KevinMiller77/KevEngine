#ifndef __WINDOWS_WINDOW__
#define __WINDOWS_WINDOW__

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <core/math/math.h>

#include <core/utils/commonTypes.h>
#include <core/graphics/Window.h>
#include <core/graphics/GLContext.h>

#include <glfw/glfw3.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

struct WindowsData
{
    using EventCallbackFn = std::function<void(Event&)>;
    unsigned int width, height;
    bool windowed;
    bool VSync;
    bool callbackSet = false;
    EventCallbackFn EventCallback;
};

class WindowsWindow : public Window
{

    GLFWwindow* window;
    OpenGLContext context;
    unsigned int GLFWWinCount;
    WindowInfo info;

    int InitalizeConsole();

public:
    void ToggleFullscreen() override;

    WindowsWindow(WindowInfo inf);
    ~WindowsWindow();
    
    void OnUpdate() override;

    unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;

    // Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; data.callbackSet = true; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
    bool IsWindowed() const;

    void* GetNativeWindow() override { return (void*)window; }

    void ShutDown();
    
    static WindowsData data; 
};

#endif