#ifndef __IMGUI_LAYER__
#define __IMGUI_LAYER__

#include <graphics/layers/Layer.h>

#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <events/WindowEvent.h>

#include <graphics/Window.h>

#include <../ext/imgui/imgui.h>

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(Window* Parent);
    ~ImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void ShowDockSpace();

    void Begin();
    void End();
private:
    float time = 0.0f;
    
    //Dock props
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    bool DockspaceEnabled = true;
};

#endif