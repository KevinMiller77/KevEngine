#ifndef __IMGUI_LAYER__
#define __IMGUI_LAYER__

#include "Layer.h"

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    void OnAttach() override;
    void OnDetatch() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e) override;
};

#endif