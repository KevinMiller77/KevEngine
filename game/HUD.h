#ifndef __HUD_LAYER__
#define __HUD_LAYER__


#include "../src/core/graphics/layers/Layer.h"

#include <core/events/MouseEvent.h>
#include <core/events/KeyEvent.h>
#include <core/events/WindowEvent.h>
#include <core/graphics/layers/Layer.h>
#include <core/graphics/layers/Group.h>
#include <core/graphics/renderables/Sprite2D.h>
#include <core/graphics/renderables/Label.h>
#include <core/graphics/BetterGL2DRenderer.h>
#include <core/math/math.h>
#include <core/utils/Logging.h>

class HUD : public Layer
{
    Label* FrameCounter;
    Label* UpdateCounter;

public:
    HUD(unsigned int shader);
    ~HUD() override;

    void OnAttach() override;
    void OnDetatch() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e);
};

#endif