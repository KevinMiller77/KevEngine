#include "HUD.h"

HUD::HUD(unsigned int shader)
    :   Layer(new BetterGL2DRenderer(), shader)
{
}

HUD::~HUD()
{
    for (Renderable2D* renderable : renderables)
    {
        delete renderable;
    }
}

void HUD::OnAttach()
{
    fonts.Add("arial", "resources/fonts/arial.ttf", 32);
    fonts.Add("inkfree", "resources/fonts/INKFREE.TTF", 28);

    Group* FrameCounterGroup = new Group(Mat4f::translation(Vec3f(-16, -9, 0)));

    FrameCounterGroup->Add(new Sprite(0.2, 0.3, 5.0, 1.5, Vec4f(0.3f, 0.3f, 0.3f, 1.0f)));
    FrameCounter = new Label("", 0.3f, 1.3, fonts.Get("inkfree"), Vec4f(0, 0, 0, 1));
    
    FrameCounterGroup->Add(new Sprite(0.2, 1.8, 5.0, 1.5, Vec4f(0.3f, 0.3f, 0.3f, 1.0f)));
    UpdateCounter = new Label("", 0.3f, 2.8, fonts.Get("inkfree"), Vec4f(0, 0, 0, 1));
    FrameCounterGroup->Add(FrameCounter);
    FrameCounterGroup->Add(UpdateCounter);
    
    Add(FrameCounterGroup);
}

void HUD::OnDetach()
{

}

extern unsigned int LastFrameKeep;
extern unsigned int LastUpdateKeep;
void HUD::OnUpdate()
{
    //char* text; sprintf(text, "FPS: %d", LastFrameKeep);
    FrameCounter->SetText("FPS: " + to_string(LastFrameKeep));
    UpdateCounter->SetText("UPS: " + to_string(LastUpdateKeep));
}

void HUD::OnDraw()
{
    Render();
}

void HUD::OnEvent(Event& e)
{
}