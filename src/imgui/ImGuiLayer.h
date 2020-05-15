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
    ImGuiLayer(Window* Parent)
    : Layer(Parent, nullptr, 0, nullptr)
    {}
    
    ~ImGuiLayer() = default;

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

    virtual void ShowDockSpace() = 0;

    virtual void Begin() = 0;
    virtual void End() = 0;
    
    virtual void OnUpdate() = 0;
    
    static ImGuiLayer* Create(Window* Parent);
};

#endif
