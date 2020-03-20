#ifndef __IMGUI_LAYER__
#define __IMGUI_LAYER__

#include <graphics/layers/Layer.h>

#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <events/WindowEvent.h>

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

    void Begin();
    void End();
private:
    float time = 0.0f;
};

#endif