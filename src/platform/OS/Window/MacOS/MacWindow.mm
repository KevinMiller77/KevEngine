#include "MacWindow.h"

MacData MacWindow::data = MacData();

void GLFWErrorCallback(int error, const char* decsription)
{
    LOG_ERR("GLFW ERR [%X]: %s\n", error, decsription);
}

void MacWindow::CallWindowHints()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

MacWindow::~MacWindow()
{
    ShutDown();
}

MacWindow::MacWindow(WindowInfo inf)
    : m_Context(nullptr), GLFWWinCount(0)
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
    CallWindowHints();

    window = glfwCreateWindow((int)data.width, (int)data.height, info.Title, nullptr, nullptr);
    LOG_INF("Made window\n");
    
    device = MTLCreateSystemDefaultDevice();
    queue = [device newCommandQueue];
    
    m_Context = (MetalContextLayer*)Context::Create(window);
    m_Context->Init(device, window);

    glfwSetWindowUserPointer(window, &data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(Vec2u(data.width, data.height));
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
    {
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);

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
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event((keycode));
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);

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
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
    {
        MacData& data = *(MacData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event(Vec2f((float)xPos, (float)yPos));
        data.EventCallback(event);
    });
}

void MacWindow::ToggleFullscreen()
{    
    if (glfwGetWindowMonitor(window))
    {
        glfwSetWindowMonitor(window, NULL, data.windowed_x, data.windowed_y, data.w_width, data.w_height, 0);
        data.windowed = true;
    }
    else
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if (monitor)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwGetWindowPos(window, &(data.windowed_x), &(data.windowed_y));
            glfwGetWindowSize(window, &(data.w_width), &(data.w_height));
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        data.windowed = false;
    }
}

void MacWindow::OnUpdate()
{
    glfwPollEvents();
    m_Context->SwapBuffers();
}

unsigned int* MacWindow::GetWidthPtr() const
{
    return &(data.width);
}
unsigned int* MacWindow::GetHeightPtr() const
{
    return &(data.height);
}

unsigned int MacWindow::GetWidth() const
{
    return data.width;
}


unsigned int MacWindow::GetHeight() const
{
    
    return data.height;
}

void MacWindow::ShutDown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void MacWindow::SetVSync(bool enabled)
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

bool MacWindow::IsVSync() const
{
    return data.VSync;
}
