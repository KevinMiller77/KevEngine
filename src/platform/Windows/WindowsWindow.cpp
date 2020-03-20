#include "WindowsWindow.h"

// TODO(Adin): Switch to CreateWindowEx

WindowsData WindowsWindow::data = WindowsData();

void GLFWErrorCallback(int error, const char* decsription)
{
    LOG_ERR("GLFW ERR [%X]: %s\n", decsription);
}

WindowsWindow::~WindowsWindow()
{
    ShutDown();
}

WindowsWindow::WindowsWindow(WindowInfo inf)
    : context(nullptr), GLFWWinCount(0)
{
    info = inf;
    data.height = info.Height; data.width = info.Width;

    LOG_INF("Creating window\n");

    if (GLFWWinCount == 0)
    {
        if (!glfwInit())
        {
            LOG_ERR("Could not init GLFW!!\n");
        }
        else
        {
            LOG_INF("GLFW Init\n");
        }
        glfwSetErrorCallback(GLFWErrorCallback);
    }
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow((int)data.width, (int)data.height, info.Title, nullptr, nullptr);

    context = OpenGLContext(window);
    context.Init();

    glfwSetWindowUserPointer(window, &data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(Vec2u(data.width, data.height));
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event((key), 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event((key));
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event((key), 1);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event((keycode));
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event((MouseCode)(button));
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event((MouseCode)(button));
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event(Vec2f((float)xPos, (float)yPos));
        data.EventCallback(event);
    });
}

int WindowsWindow::InitalizeConsole()
{
    BOOL success = AllocConsole();
    if (!success)
    {
        DebugBreak();
        return 1;

    }

    FILE *newStdout;
    FILE *newStdin;
    FILE *newStderr;

    freopen_s(&newStdout, "CONOUT$", "w", stdout);
    freopen_s(&newStdin, "CONIN$", "r", stdin);
    freopen_s(&newStderr, "CONOUT$", "w", stderr);

    return 0;
}

void WindowsWindow::ToggleFullscreen()
{    
    //TODO: Fullscreen toggle
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    context.SwapBuffers();
}

unsigned int WindowsWindow::GetWidth() const
{
    return data.width;
}


unsigned int WindowsWindow::GetHeight() const
{
    
    return data.height;
}

void WindowsWindow::ShutDown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowsWindow::SetVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return data.VSync;
}