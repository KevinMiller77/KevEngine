
#include <core/Core.h>

#ifdef KEV_PLATFORM_EM
    #include <emscripten/emscripten.h>
#else
    #include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <assert.h>
#include "GLContext.h"

GLContext::GLContext(GLFWwindow* windowHandle)
    : window(windowHandle)
{
}

void GLContext::Init()
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

void GLContext::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void GLContext::SetView(int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}
