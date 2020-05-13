#include "HUD.h"
#include <core/KevEngine.h>

HUD::HUD(Window* Parent, unsigned int shader, Kev2DCamera* Camera)
    :   Layer(Parent, new GLRenderer2D((int*)Parent->GetWidthPtr(), (int*)Parent->GetHeightPtr()), shader, Camera)
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
    fonts.Add("arial", "/Users/kevinmiller/dev/kevengine/resources/fonts/arial.ttf", 32);
    fonts.Add("inkfree", "/Users/kevinmiller/dev/kevengine/resources/fonts/INKFREE.TTF", 28);

    FrameCounterGroup = new Group(Mat4f::translation(Vec3f(-16, -9, 0)));

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
    Vec2f camPos = camera->GetWorldPos(16.0f, 9.0f);
    float curZoom = camera->GetZoomLevel();
    FrameCounterGroup->SetPosition(new Vec3f(camPos.x - (16.0f * curZoom), camPos.y - (9.0f * curZoom), 0));
    //char* text; sprintf(text, "FPS: %d", LastFrameKeep);
    FrameCounter->SetText("FPS: " + to_string(KevEngine::LastFrameKeep));
    UpdateCounter->SetText("UPS: " + to_string(KevEngine::LastUpdateKeep));
}

void HUD::OnDraw()
{
    Render();
}

void HUD::OnEvent(Event& e)
{
}
