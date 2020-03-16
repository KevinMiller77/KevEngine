#ifndef __GAME_LAYER__
#define __GAME_LAYER__

#include "../src/core/graphics/layers/Layer.h"

#include <core/events/MouseEvent.h>
#include <core/events/KeyEvent.h>
#include <core/events/WindowEvent.h>
#include <core/graphics/layers/Layer.h>
#include <core/graphics/layers/Group.h>
#include <core/graphics/BetterGL2DRenderer.h>
#include <core/math/math.h>
#include <core/utils/Logging.h>
#include <core/graphics/OrthographicCameraController.h>

class GameLayer : public Layer
{
    Vec2u screenSize = Vec2u(1280, 720);
    Vec2u mousePos;

    bool GameLayer::MouseScroll(MouseScrolledEvent& e);

    OrthographicCameraController camera;

public:
    GameLayer(unsigned int shader);
    ~GameLayer() override;

    void OnAttach() override;
    void OnDetatch() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e);
};

#endif