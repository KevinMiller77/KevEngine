#ifndef __CONTEXT__
#define __CONTEXT__

#include <utils/Logging.h>
#include <GLFW/glfw3.h>

class Context
{
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetView(int Width, int Height) = 0;

    static Context* Create(GLFWwindow* windowHandle);
};

#endif
