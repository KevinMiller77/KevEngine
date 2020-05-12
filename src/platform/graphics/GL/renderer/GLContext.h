#ifndef __GL_CONTEXT__
#define __GL_CONTEXT__

#include <utils/Logging.h>
#include <GLFW/glfw3.h>

class OpenGLContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void Init();
    virtual void SwapBuffers();
    virtual void SetView(int Width, int Height);

private:
    GLFWwindow* window;
};

#endif