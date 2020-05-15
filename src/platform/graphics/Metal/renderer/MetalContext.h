#ifndef __Metal_MW_CONTEXT__
#define __Metal_MW_CONTEXT__

#include <utils/Logging.h>
#include <graphics/api/Context.h>

#ifdef KEV_RENDERAPI_METAL
    #define GLFW_INCLUDE_NONE
    #define GLFW_EXPOSE_NATIVE_COCOA
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>
#endif
#ifdef KEV_PLATFORM_MACOS
    #import <Metal/Metal.h>
    #import <QuartzCore/QuartzCore.h>
#endif


//A Metal Context holds the device, commandQueue, and the NSWindow that is required
//  TO display anything on the screen. It is not a context like GL has!!
class MetalContextLayer : public Context
{
public:
    MetalContextLayer(GLFWwindow* windowHandle);

    virtual void Init() override {}
    virtual void Init(id<MTLDevice> device, GLFWwindow* Window);
    virtual void SwapBuffers() override;
    virtual void SetView(int Width, int Height) override;
    
    inline CAMetalLayer* GetIntLayer() { return m_MetalLayer; }

private:
    GLFWwindow* m_Window;
    CAMetalLayer* m_MetalLayer;
};

#endif
