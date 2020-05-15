
#include <core/Core.h>

#include <assert.h>
#include "MetalContext.h"
#include <platform/graphics/Metal/Metal.h>

MetalContextLayer::MetalContextLayer(GLFWwindow* windowHandle)
    : m_Window(windowHandle)
{
}

void MetalContextLayer::Init(id<MTLDevice> Device, GLFWwindow* Window)
{
    // Setup Platform/Renderer bindings
    NSWindow* nsWin = glfwGetCocoaWindow(Window);
    m_MetalLayer = [CAMetalLayer layer];
    m_MetalLayer.device = Device;
    m_MetalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    nsWin.contentView.layer = m_MetalLayer;
    nsWin.contentView.wantsLayer = YES;
}

void MetalContextLayer::SwapBuffers()
{
}

void MetalContextLayer::SetView(int Width, int Height)
{
    //TODO: Metal viewport set
}
