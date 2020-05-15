#include "ImGuiLayer.h"
#include <core/Core.h>

#include <platform/graphics/GL/imgui/GLImGuiLayer.h>
#include <platform/graphics/Metal/imgui/MetalImGuiLayer.h>

ImGuiLayer* ImGuiLayer::Create(Window* Parent)
{
#ifdef KEV_RENDERAPI_GL
    return new GLImGuiLayer(Parent);
#elif defined KEV_RENDERAPI_METAL
    return new MetalImGuiLayer(Parent);
#endif
}
