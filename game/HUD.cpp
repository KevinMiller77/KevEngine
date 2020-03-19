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
    fonts.add("arial", "resources/fonts/arial.ttf", 32);
    fonts.add("inkfree", "resources/fonts/INKFREE.ttf", 28);

    Group* FrameCounterGroup = new Group(Mat4f::translation(Vec3f(-16, -9, 0)));

    FrameCounterGroup->add(new Sprite(0.2, 0.3, 5.0, 1.5, Vec4f(0.3f, 0.3f, 0.3f, 1.0f)));
    FrameCounter = new Label("", 0.3f, 1.3, fonts.get("inkfree"), Vec4f(0, 0, 0, 1));
    
    FrameCounterGroup->add(new Sprite(0.2, 1.8, 5.0, 1.5, Vec4f(0.3f, 0.3f, 0.3f, 1.0f)));
    UpdateCounter = new Label("", 0.3f, 2.8, fonts.get("inkfree"), Vec4f(0, 0, 0, 1));
    FrameCounterGroup->add(FrameCounter);
    FrameCounterGroup->add(UpdateCounter);
    
    add(FrameCounterGroup);
}

void HUD::OnDetatch()
{

}

extern unsigned int LastFrameKeep;
extern unsigned int LastUpdateKeep;
void HUD::OnUpdate()
{
    //char* text; sprintf(text, "FPS: %d", LastFrameKeep);
    FrameCounter->setText("FPS: " + to_string(LastFrameKeep));
    UpdateCounter->setText("UPS: " + to_string(LastUpdateKeep));
}

void HUD::OnDraw()
{
    render();
}

void HUD::OnEvent(Event& e)
{
}