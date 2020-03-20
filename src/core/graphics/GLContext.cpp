#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "GLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : window(windowHandle)
{
}

void OpenGLContext::Init()
{
    if (window != nullptr)
    {
        glfwMakeContextCurrent(window);
    }
    else
    {
        LOG_ERR("NO CONTEXT COULD BE CREATED\n");
    }
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERR("Gl could not load!\n");
    }

    int versionMajor;
    int versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    LOG_INF("GL Init. MAJOR: %d\tMINOR: %d\n", versionMajor, versionMinor);
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(window);
}