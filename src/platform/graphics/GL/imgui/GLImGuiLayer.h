#ifndef __GL_IMGUI_LAYER__
#define __GL_IMGUI_LAYER__

#include <imgui/ImGuiLayer.h>

class GLImGuiLayer : public ImGuiLayer
{
public:
    GLImGuiLayer(Window* Parent);

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void ShowDockSpace() override;

    virtual void Begin() override;
    virtual void End() override;
    
    virtual void OnUpdate() override {}
private:
    float time = 0.0f;
    
    //Dock props
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    bool DockspaceEnabled = true;
};

#endif
