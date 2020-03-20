#ifndef __HUD_LAYER__
#define __HUD_LAYER__

#include <events/MouseEvent.h>
#include <events/KeyEvent.h>
#include <events/WindowEvent.h>
#include <graphics/layers/Layer.h>
#include <graphics/layers/Group.h>
#include <graphics/renderables/Sprite2D.h>
#include <graphics/renderables/Label.h>
#include <graphics/BetterGL2DRenderer.h>
#include <math/math.h>
#include <utils/Logging.h>

class HUD : public Layer
{
    Label* FrameCounter;
    Label* UpdateCounter;

public:
    HUD(unsigned int shader);
    ~HUD() override;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e);
};

#endif