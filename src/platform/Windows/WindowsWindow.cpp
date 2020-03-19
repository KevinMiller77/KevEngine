#include "WindowsWindow.h"

/*
  OpenGL Reference Wiki:
  https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
*/

// TODO(Adin): Switch to CreateWindowEx

WindowsData WindowsWindow::data = WindowsData();

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

int WindowsWindow::InitalizeConsole()
{
    BOOL success = AllocConsole();
    if (!success)
    {
        // if (!FreeConsole())
        // {
            DebugBreak();
            return 1;
        // }

        // BOOL success2 = AllocConsole();
        // if (!success2)
        // {
        //     DebugBreak();
        //     return 1;
        // }

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

int WindowsWindow::LoadGLExtensions(HINSTANCE hInstance)
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

    UnregisterClass("DummyName", hInstance);

    return 0;
}

HGLRC WindowsWindow::CreateGLContext()
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
        WindowCloseEvent event;
        WindowsWindow::data.EventCallback(event);
        PostQuitMessage(0);
    }
    break;

    case WM_SIZE:
    {
        // Also call render function here
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        HDC tempHDC = GetDC(hwnd);
        WindowResizeEvent event = WindowResizeEvent((Vec2u(LOWORD(lParam), HIWORD(lParam))));
        if (WindowsWindow::data.callbackSet)
        {
            WindowsWindow::data.EventCallback(event);
        }
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

bool WindowsWindow::restartGLContext()
{
    HGLRC currentContext = wglGetCurrentContext();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(currentContext);

    HGLRC gameGLContext = CreateGLContext();
    if ( gameGLContext == 0)
    {
        LOG_ERR("Could not restart context. Leaving program\n");
        return false;
    }
    wglMakeCurrent(windowHDC, gameGLContext);

    return true;
}

void WindowsWindow::ToggleFullscreen()
{    
    if ( data.windowed )
    {
        GetWindowPlacement( window, &wpc);
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
    data.windowed = !data.windowed;

    keyDebounce.start();
}

WindowsWindow::WindowsWindow(WindowInfo inf)
{
    info = inf;
    hInstance = HINST_THISCOMPONENT;
    InitalizeConsole();

    WNDCLASSEX wc = {};
    wc.hInstance = hInstance;
    wc.lpszClassName = (LPCSTR)inf.Title;
    wc.lpfnWndProc = WindowProc;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.cbSize = sizeof(WNDCLASSEX);
    
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;   
    wc.cbClsExtra = 0;            
    wc.cbWndExtra = 0;

    RegisterClassEx(&wc);
    
    // GLEW is initalized in here
    LoadGLExtensions(hInstance);

    RECT r = {0, 0, KEV_ENGINE_WINDOW_X, KEV_ENGINE_WINDOW_Y};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);

    window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, (LPCSTR)inf.Title, "KevGame", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top, HWND_DESKTOP, NULL, hInstance, NULL);

    windowHDC = GetDC(window);
    
    //HGLRC baseGLContext = CreateGLContext(windowHDC);
    gameGLContext = CreateGLContext();

    wglMakeCurrent(windowHDC, gameGLContext);
    data.windowed = true;

    // TODO(Adin): Investigate why this needs "%s"
    LOG(DBG, "%s\n", glGetString(GL_VERSION));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    ShowWindow(window, SW_SHOW);
}

void WindowsWindow::OnUpdate()
{
    MSG message = {};

    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {

        switch (message.message)
        {
    
        case (WM_QUIT):
        {
            // Quit when it's quittin time
            WindowCloseEvent event;
            data.EventCallback(event);
            break;
        }
    
        case (WM_MOUSEMOVE):
        {
            MouseMovedEvent event = MouseMovedEvent(Vec2u(LOWORD(message.lParam), HIWORD(message.lParam)));
            data.EventCallback(event);
            Input::SetMousePos(Vec2u(LOWORD(message.lParam), HIWORD(message.lParam)));
            break;
        }
        case (WM_MOUSEWHEEL):
        {
            MouseScrolledEvent event = MouseScrolledEvent(0, (int)message.wParam / WHEEL_DELTA);
            data.EventCallback(event);
            break;
        }
        case (WM_MOUSEHWHEEL):
        {
            MouseScrolledEvent event((int)message.wParam / WHEEL_DELTA, 0);
            data.EventCallback(event);
            break;
        }    

        case (WM_MOUSELEAVE):
        {
            WindowLostFocusEvent event;
            data.EventCallback(event);
            break;
        }

        case (WM_MOUSEACTIVATE):
        {
            WindowFocusEvent event;
            data.EventCallback(event);
            break;
        }
        case (WM_KEYDOWN):
        {
            if (keyDebounce.getTimePassed() < KEY_DEBOUNCE_TIME) break;
            keyDebounce.reset();
            KeyPressedEvent event = KeyPressedEvent(message.wParam, message.lParam & 0xFFFF0000);
            data.EventCallback(event);
            Input::SetKeyPressed((KeyCode)message.wParam);
            break;
        }

        case (WM_KEYUP):
        {
            KeyReleasedEvent event = KeyReleasedEvent(message.wParam);
            data.EventCallback(event);
            Input::SetKeyReleased((KeyCode)message.wParam);
            break;
        }

        case (WM_MBUTTONDOWN): case (WM_LBUTTONDOWN): case (WM_RBUTTONDOWN): case (WM_XBUTTONDOWN):
        {
            MouseCode code = (MouseCode)(unsigned int)log2(message.wParam + 0.1f);
            MouseButtonPressedEvent event = MouseButtonPressedEvent(code);
            data.EventCallback(event);
            Input::SetMouseButtonPressed(code);
            break;
        }

        case (WM_MBUTTONUP): case (WM_LBUTTONUP): case (WM_RBUTTONUP): case (WM_XBUTTONUP):
        {
            MouseCode code = (MouseCode)(unsigned int)log2(message.wParam + 0.1f);
            MouseButtonReleasedEvent event = MouseButtonReleasedEvent(code);
            data.EventCallback(event);
            Input::SetMouseButtonReleased(code);
            break;
        }

        default:
            break;
        }
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    SwapBuffers(windowHDC);
}

unsigned int WindowsWindow::GetWidth() const
{
    RECT rect;
    if (GetWindowRect(window, &rect))
        return rect.right - rect.left;
}


unsigned int WindowsWindow::GetHeight() const
{
    RECT rect;
    if (GetWindowRect(window, &rect))
        return rect.bottom - rect.top;
}

Vec2u WindowsWindow::GetMousePos() const
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(window, &pt);
    return Vec2u(pt.x, pt.y);
}

void WindowsWindow::ShutDown()
{
    // These are probably unnecessary because the window is already destroyed
    ReleaseDC(window, windowHDC);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(gameGLContext);
}

void WindowsWindow::SetVSync(bool enabled)
{
#if WGL_EXT_swap_control
    if (enabled) {
        wglSwapIntervalEXT(1);
        data.VSync = true;
    }
    else
    {
        wglSwapIntervalEXT(0);
        data.VSync = false;
    }
#endif
}

bool WindowsWindow::IsVSync() const
{
    return data.VSync;
}