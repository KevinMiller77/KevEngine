
#include <core/Core.h>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#ifdef KEV_PLATFORM_EM
    <emscripten/emscripten.h>
#else
#endif

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
    
#ifdef KEV_PLATFORM_EM
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)))
#else
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
#endif
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

void OpenGLContext::SetView(int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}