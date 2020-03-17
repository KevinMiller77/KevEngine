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
#include <core/utils/Timer.h>
#include <core/graphics/cameras/FollowRenderableCamera.h>

class GameLayer : public Layer
{
    Vec2u screenSize = Vec2u(1280, 720);
    Vec2u mousePos;

    bool GameLayer::MouseScroll(MouseScrolledEvent& e);

    FollowRenderableCamera camera;
    Renderable2D* player;
    Vec2f playerVelocity = Vec2f(0, 0);
    float acceleration = 0.05f;
    float maxAcceleration = 0.30f;
    float maxJumpAcceleration = 2.0f;
    bool jumping = false;
    int jumpCount = 0;
    bool onGround = false;
    Timer updateTime;

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