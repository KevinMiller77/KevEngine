#ifndef __GL_CONTEXT__
#define __GL_CONTEXT__

#include <utils/Logging.h>
#include <GLFW/glfw3.h>

#include <graphics/api/Context.h>

class GLContext : public Context
{
public:
    GLContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;
    virtual void SetView(int Width, int Height) override;

private:
    GLFWwindow* window;
};

#endif
