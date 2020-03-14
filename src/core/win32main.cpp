#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <windows.h>
#include <wingdi.h>

#define  GLEW_BUILD GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>

#include "math/math.h"
#include "utils/commonTypes.h"
#include "KevEngine.h"

#define WINDOW_CLASS_NAME "KevEngineTestWindowClass"

#define TICK_RATE 1000;
#define FRAME_RATE 60;

MemoryMetrics memoryTracker;

void* operator new(size_t size)
{   
    memoryTracker.add(size);
    return malloc(size);
}

void operator delete(void* data, size_t size)
{
    memoryTracker.del(size);
    free(data);
}

extern KevEngine* engine;

/*
  OpenGL Reference Wiki:
  https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
*/

// TODO(Adin): Switch to CreateWindowEx

HDC windowHDC;
HWND window;
WINDOWPLACEMENT wpc;
long HWNDStyle = 0;
long HWNDStyleEx = 0;

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);

    (void)source;
    (void)userParam;
    (void)message;
    (void)length;
    (void)id;
}

int InitalizeConsole()
{
    BOOL success = AllocConsole();
    if (!success)
    {
        DebugBreak();
        return 1;
    }

    // TODO(Adin): If possible get the first method to work it seems
    //             like it might be a better solution
#if 0
    HANDLE sysHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(sysHandle == INVALID_HANDLE_VALUE) {
        int temp = GetLastError();
        (void) temp;
        DebugBreak();
        return 1;
    }
    
    int fd = _open_osfhandle((intptr_t) sysHandle, _O_TEXT);
    if(fd < 0) {
        int temp = GetLastError();
        (void) temp;
        DebugBreak();
        return 1;
    }
    
    FILE *stdoutFile = _fdopen(fd, "w");
    if(stdoutFile == NULL) {
        char *error = strerror(errno);
        (void) error;
        DebugBreak();
        return 1;
    }
    
    *stdout = *stdoutFile;
    setvbuf(stdout, NULL, _IONBF, 0);
    
    return 0;
#endif

    // TODO(Adin): return codes and error handling when error system is implemented

    FILE *newStdout;
    FILE *newStdin;
    FILE *newStderr;

    freopen_s(&newStdout, "CONOUT$", "w", stdout);
    freopen_s(&newStdin, "CONIN$", "r", stdin);
    freopen_s(&newStderr, "CONOUT$", "w", stderr);

    return 0;
}

int LoadGLExtensions(HINSTANCE hInstance)
{
    const char DummyWindowClassName[] = "KevEngineDummyWinClass";

    WNDCLASS dummyWindowClass = {};
    dummyWindowClass.style = CS_OWNDC;
    dummyWindowClass.lpfnWndProc = DefWindowProc;
    dummyWindowClass.hInstance = hInstance;
    dummyWindowClass.lpszClassName = DummyWindowClassName;

    RegisterClass(&dummyWindowClass);

    HWND dummyWindow = CreateWindow(DummyWindowClassName, "Dummy Thicc", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (dummyWindow == NULL)
    {
        printf("Failed to create dummy window!\n");
        return 1;
    }

    // Default dummy descriptor values copied from opengl wiki
    PIXELFORMATDESCRIPTOR dummyDescriptor = {};
    dummyDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    dummyDescriptor.nVersion = 1;
    dummyDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    dummyDescriptor.iPixelType = PFD_TYPE_RGBA;
    dummyDescriptor.cColorBits = 32;
    dummyDescriptor.cDepthBits = 24;
    dummyDescriptor.cStencilBits = 8;
    dummyDescriptor.iLayerType = PFD_MAIN_PLANE;

    HDC dummyDC = GetDC(dummyWindow);
    if (dummyDC == NULL)
    {
        printf("Failed to get dummy window HDC!\n");
        DestroyWindow(dummyWindow);
        return 1;
    }

    int dummyPixelFormat = ChoosePixelFormat(dummyDC, &dummyDescriptor);
    SetPixelFormat(dummyDC, dummyPixelFormat, &dummyDescriptor);

    HGLRC dummyWGLHandle = wglCreateContext(dummyDC);
    wglMakeCurrent(dummyDC, dummyWGLHandle);

    // Don't need this anymore
    ReleaseDC(dummyWindow, dummyDC);

    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        printf("GLEW failed to init: %s\n", glewGetErrorString(glewInitResult));

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(dummyWGLHandle);

        DestroyWindow(dummyWindow);

        return 1;
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dummyWGLHandle);

    DestroyWindow(dummyWindow);

    UnregisterClass(DummyWindowClassName, hInstance);

    return 0;
}

HGLRC CreateGLContext(HDC windowHDC)
{
    HGLRC result = NULL;

    // Default attributes copied from opengl wiki
    const int pfAttributeList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0 // Null terminator
    };

    int pixelFormatIndex = 0;
    UINT numPixelFormats = 0;

    // Needed for the set pixel format call but not actually important or used
    PIXELFORMATDESCRIPTOR blankPFD = {};
    blankPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    blankPFD.nVersion = 1;

    wglChoosePixelFormatARB(windowHDC, pfAttributeList, NULL, 1, &pixelFormatIndex, &numPixelFormats);

    SetPixelFormat(windowHDC, pixelFormatIndex, &blankPFD);

    // GL 3.2 debug context
    const int contextAttributeList[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 2,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
        0 // Null terminator
    };

    result = wglCreateContextAttribsARB(windowHDC, NULL, contextAttributeList);

    return result;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    break;

    case WM_SIZE:
    {
        // Also call render function here
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));

        HDC tempHDC = GetDC(hwnd);
        engine->setScreenResolution(Vec2u(LOWORD(lParam), HIWORD(lParam)));
        engine->Draw();
        ReleaseDC(hwnd, tempHDC);
        SwapBuffers(tempHDC);
        return 0;
    }
    break;

    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

bool restartGLContext()
{
    HGLRC currentContext = wglGetCurrentContext();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(currentContext);

    HGLRC gameGLContext = CreateGLContext(windowHDC);
    if ( gameGLContext == 0)
    {
        LOG_ERR("Could not restart context. Leaving program\n");
        return false;
    }
    wglMakeCurrent(windowHDC, gameGLContext);

    return true;
}

bool ToggleFullscreen()
{    
    bool windowedMode = engine->getWindowMode();
    if ( windowedMode )
    {
        GetWindowPlacement( window, &wpc );
        if ( HWNDStyle == 0 )
            HWNDStyle = GetWindowLong( window, GWL_STYLE );
        if ( HWNDStyleEx == 0 )
            HWNDStyleEx = GetWindowLong( window, GWL_EXSTYLE );

        LONG NewHWNDStyle = HWNDStyle;
        NewHWNDStyle &= ~WS_BORDER;
        NewHWNDStyle &= ~WS_DLGFRAME;
        NewHWNDStyle &= ~WS_THICKFRAME;

        LONG NewHWNDStyleEx =HWNDStyleEx;
        NewHWNDStyleEx &= ~WS_EX_WINDOWEDGE;

        SetWindowLong( window, GWL_STYLE, NewHWNDStyle | WS_POPUP );
        SetWindowLong( window, GWL_EXSTYLE, NewHWNDStyleEx | WS_EX_TOPMOST );
        ShowWindow( window, SW_SHOWMAXIMIZED );
    }
    else
    {
        SetWindowLong( window, GWL_STYLE, HWNDStyle );
        SetWindowLong( window, GWL_EXSTYLE, HWNDStyleEx );
        ShowWindow( window, SW_SHOWNORMAL );
        SetWindowPlacement( window, &wpc );
    }

    return !windowedMode;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;

    InitalizeConsole();

    WNDCLASS wc = {};
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&wc);

    // GLEW is initalized in here
    LoadGLExtensions(hInstance);

    window = CreateWindow(WINDOW_CLASS_NAME, "KevEngine Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 960, 540, NULL, NULL, hInstance, NULL);
    
    windowHDC = GetDC(window);

    engine->restartContext = restartGLContext;
    engine->toggleFullScreen = ToggleFullscreen;
    
    //HGLRC baseGLContext = CreateGLContext(windowHDC);
    HGLRC gameGLContext = CreateGLContext(windowHDC);

    wglMakeCurrent(windowHDC, gameGLContext);

    // TODO(Adin): Investigate why this needs "%s"
    LOG(DBG, "%s\n", glGetString(GL_VERSION));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    //Game start actions
    engine->restartContext();
    engine->OnGameStart();
    ShowWindow(window, SW_SHOW);

    // Main loop
    MSG message = {};
    BOOL running = TRUE;
    
    InputInformation state;
    Timer onUpdateTimer;
    onUpdateTimer.start();

    float updateConstant = 1.0f / 240.0f;
    double timeNow = onUpdateTimer.getTimePassed();

    while (running)
    {
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            SwapBuffers(windowHDC);
            state = InputInformation();
            state._mouseWheelMagConstant = WHEEL_DELTA;
            switch (message.message)
            {

            case (WM_QUIT):
                // Quit when it's quittin time
                running = false;
                break;

            case (WM_MOUSEMOVE):
                state._mouseButtons = message.wParam;
                state._mousePos = Vec2u(LOWORD(message.lParam), HIWORD(message.lParam));
                state._mouseWheelMag = 0;
#if IMMERSIVE_CURSOR                    
                {
                    RECT rect = { NULL };
                    if (GetWindowRect(window, &rect))
                    {
                        Vec2u resolution = engine->getScreenResolution();
                        SetCursorPos(resolution.x / 2 + rect.left, resolution.y / 2 + rect.top);
                        ShowCursor(false);
                    }
                }
#endif
                
                break;

            case (WM_MOUSEWHEEL):
                state._mouseWheelMag = message.wParam;
                state._mousePos = Vec2u(LOWORD(message.lParam), HIWORD(message.lParam));
                break;
            
            case (WM_MOUSELEAVE):
                ShowCursor(true);

            case (WM_KEYDOWN):
                state._key = (uint8_t)(message.wParam);
                state._holdCount = (uint16_t)(message.lParam & 0xFFFF0000);
                state._extendedKey = (bool)(message.lParam & 0x00000800);
                state._previousKeyState = (bool)(message.lParam & 0x00000004);
                break;
            
            case (WM_MBUTTONDOWN): case (WM_LBUTTONDOWN): case (WM_RBUTTONDOWN): case (WM_XBUTTONDOWN):
                LOG_INF("Mouse key: %d\n", (int)log2(message.wParam));
                break;

            case (WM_KEYUP):
                state._key = (uint8_t)(message.wParam);
                state._holdCount = 0;
                state._direction = 1;
                state._extendedKey = (bool)(message.lParam & 0x00000800);
                break;


            default:
                break;
            }
            engine->ProcessInput(state);
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        if (onUpdateTimer.getTimePassed() - timeNow > updateConstant)
        {
            timeNow = onUpdateTimer.getTimePassed();
            engine->OnUpdate();
        }
        engine->OnTick();
        engine->Draw();
        SwapBuffers(windowHDC);
    }

    // These are probably unnecessary because the window is already destroyed
    ReleaseDC(window, windowHDC);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(gameGLContext);

    return 0;
}