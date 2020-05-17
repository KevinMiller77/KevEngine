
#ifndef __IM_GUI_TEST_LLAYER__
#define __IM_GUI_TEST_LLAYER__

#include <graphics/layers/Layer.h>
#include <graphics/renderables/Sprite.h>
#include <imgui.h>

class IGTL : public Layer
{
public:
    IGTL(Window* Parent)
    {
        
    }
    
    void OnAttach() override
    {
//        Add(new Sprite(0, 0, 2, 2, Vec4f(0.5, 0.5, 0.5, 1)));
    }
    void OnDetach() override {}

    void OnUpdate() override {}
    void OnDraw() override {}
    void OnEvent(Event& e) override {}

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("This is a test!!");
        ImGui::End();
    }
};

#endif
