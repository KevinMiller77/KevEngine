#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <windows.h>
#include <wingdi.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "utils/Logging.h"
#include "utils/FileIO.h"

#include "graphics/ShaderProgram.h"

#include "math/math.h"
#include "CommonTypes.h"
#include "TLETC.h"

#define WINDOW_CLASS_NAME "TLETCTestWindowClass"

#define TICK_RATE 1000;
#define FRAME_RATE 60;

/*
  OpenGL Reference Wiki:
  https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
*/

// TODO(Adin): Switch to CreateWindowEx

TLETC *tletc = nullptr;

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
    const char DummyWindowClassName[] = "TLETCDummyWinClass";

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
        tletc->setScreenResolution(Vec2u(LOWORD(lParam), HIWORD(lParam)));
        tletc->Draw(tempHDC);
        ReleaseDC(hwnd, tempHDC);
        return 0;
    }
    break;

    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
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

    HWND window = CreateWindow(WINDOW_CLASS_NAME, "TLETC Test Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 960, 540, NULL, NULL, hInstance, NULL);
    HDC windowHDC = GetDC(window);

    tletc = new TLETC(Vec2u(960, 540));

    HGLRC glContext = CreateGLContext(windowHDC);

    wglMakeCurrent(windowHDC, glContext);

    // TODO(Adin): Investigate why this needs "%s"
    LOG(DBG, "%s\n", glGetString(GL_VERSION));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    //Game start actions
    tletc->OnGameStart();
    ShowWindow(window, SW_SHOW);

    // Main loop
    MSG message = {};
    BOOL running = TRUE;
    //clock_t TICK_KEEP;
    //clock_t FRAME_KEEP;
    while (running)
    {
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {

            case (WM_QUIT):
                // Quit when it's quittin time
                running = false;
                break;

            case (WM_MOUSEMOVE):
                tletc->setMousePos(Vec2u(LOWORD(message.lParam), HIWORD(message.lParam)));
                break;

            default:
                break;
            }

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        tletc->Update();
        tletc->Draw(windowHDC);
    }

    // These are probably unnecessary because the window is already destroyed
    ReleaseDC(window, windowHDC);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glContext);

    return 0;
}