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

#include "../../core/math/math.h"
#include "../../core/utils/commonTypes.h"
#include "../../core/KevEngine.h"

#include "../../core/graphics/Window.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

class WindowsWindow : public Window
{
    HINSTANCE hInstance;
    HDC windowHDC;
    HWND window;
    HGLRC gameGLContext;
    WINDOWPLACEMENT wpc;
    long HWNDStyle = 0;
    long HWNDStyleEx = 0;

    WindowInfo info;

    int InitalizeConsole();
    HGLRC CreateGLContext();
    int LoadGLExtensions(HINSTANCE hInstance);

public:
    static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    bool restartGLContext();
    void ToggleFullscreen();

    WindowsWindow(WindowInfo inf);
    
    void OnUpdate() override;

    unsigned int GetWidth() const override;
	unsigned int GetHeight() const override;

    // Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
    bool IsWindowed() const;

    void ShutDown();

    struct WindowsData
    {
        unsigned int width, height;
        bool windowed;
	    bool VSync;
	    EventCallbackFn EventCallback;
    }; 
    
    static WindowsData data;
};

#endif