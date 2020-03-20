#ifndef __GL_CONTEXT__
#define __GL_CONTEXT__

#include <core/utils/Logging.h>
#include <GLFW/glfw3.h>

class OpenGLContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void Init();
    virtual void SwapBuffers();

private:
    GLFWwindow* window;
};

#endif