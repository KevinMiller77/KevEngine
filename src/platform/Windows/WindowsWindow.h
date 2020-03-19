#ifndef __WINDOWS_WINDOW__
#define __WINDOWS_WINDOW__

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <windows.h>
#include <wingdi.h>

#define  GLEW_BUILD GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>

#include <core/math/math.h>
#include <core/utils/commonTypes.h>
#include <core/KevEngine.h>

#include <core/graphics/Window.h>
#include <core/Input.h>

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
    HINSTANCE hInstance;
    HDC windowHDC;
    HWND window;
    HGLRC gameGLContext;
    WINDOWPLACEMENT wpc;
    long HWNDStyle = 0;
    long HWNDStyleEx = 0;

    Timer keyDebounce;

    WindowInfo info;

    int InitalizeConsole();
    HGLRC CreateGLContext();
    int LoadGLExtensions(HINSTANCE hInstance);

public:
    bool restartGLContext();
    void ToggleFullscreen() override;

    WindowsWindow(WindowInfo inf);
    
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