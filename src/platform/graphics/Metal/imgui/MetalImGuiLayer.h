#ifndef __METAL_IMGUI_LAYER__
#define __METAL_IMGUI_LAYER__

#include <imgui/ImGuiLayer.h>

#include <imgui.h>
#include <examples/imgui_impl_metal.h>
#include <examples/imgui_impl_glfw.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#include <platform/graphics/Metal/Metal.h>

#include <core/KevEngine.h>


class MetalImGuiLayer : public ImGuiLayer
{
public:
    MetalImGuiLayer(Window* Parent);
    ~MetalImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void ShowDockSpace() override;

    virtual void Begin() override;
    virtual void End() override;
    
    virtual void OnUpdate() override {}
private:
    MTLRenderPassDescriptor *RPD;
    id <MTLRenderCommandEncoder> RE;
    id <MTLCommandBuffer> CB;
    id<CAMetalDrawable> drawable;
    CAMetalLayer* layer;
    
    float time = 0.0f;
    
    //Dock props
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    bool DockspaceEnabled = true;
};

#endif
