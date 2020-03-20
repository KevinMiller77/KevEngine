#ifndef __GAME_LAYER__
#define __GAME_LAYER__


#include <core/events/InputCodes.h>
#include <core/events/MouseEvent.h>
#include <core/events/KeyEvent.h>
#include <core/events/WindowEvent.h>
#include <core/graphics/layers/Layer.h>
#include <core/graphics/renderables/Sprite2D.h>
#include <core/graphics/layers/Group.h>
#include "../src/core/graphics/layers/Layer.h"
#include <core/graphics/BetterGL2DRenderer.h>
#include <core/math/math.h>
#include <core/utils/Logging.h>
#include <core/utils/Timer.h>
#include <core/graphics/cameras/FollowRenderableCamera.h>

class GameLayer : public Layer
{
    Vec2u screenSize;
    Vec2f screenExtremes;
    //Mouse pos adjusted to be in world space (-X, X, -Y, Y)
    Vec2f mousePos;

    bool MouseScroll(MouseScrolledEvent& e);
    bool MouseMove(MouseMovedEvent& e);
    bool WindowResize(WindowResizeEvent& e);
    bool KeyDown(KeyPressedEvent& e);

    FollowRenderableCamera camera;
    Renderable2D* player;
    Vec2f playerVelocity = Vec2f(0, 0);
    float acceleration = 0.1f;
    float maxAcceleration = 0.5f;
    float maxJumpAcceleration = 2;
    float jumpAcceleration = 0.8;
    float gravityConstant = 0.5;
    bool jumping = false;
    int jumpCount = 0;
    int maxJump = 15;
    bool onGround = false;
    Timer updateTime;

    Renderable2D* keys[0xff + 1];
    Renderable2D* mouse[18];

public:
    GameLayer(unsigned int shader, Vec2u screensize, Vec2f screenextremes = Vec2f(16, 9));
    ~GameLayer() override;

    void OnAttach() override;
    void OnDetatch() override;

    void OnUpdate() override;
    void OnDraw() override;
    void OnEvent(Event& e);
};

#endif