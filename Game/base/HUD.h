#ifndef __HUD_LAYER__
#define __HUD_LAYER__

#include <events/MouseEvent.h>
#include <events/KeyEvent.h>
#include <events/WindowEvent.h>
#include <graphics/layers/Layer.h>
#include <graphics/layers/Group.h>
#include <graphics/renderables/Sprite.h>
#include <graphics/renderables/Label.h>
#include <graphics/api/Renderer2D.h>
#include <graphics/cameras/Kev2DCamera.h>
#include <math/math.h>
#include <utils/Logging.h>

class HUD : public Layer
{
    Label* FrameCounter;
    Label* UpdateCounter;
    Group* FrameCounterGroup;

public:
    HUD(Window* Parent, ShaderProgram* shader, Kev2DCamera* Camera);
    ~HUD() override;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e) override;
};

#endif
