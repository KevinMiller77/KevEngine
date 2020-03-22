#ifndef __GAME_LAYER__
#define __GAME_LAYER__


#include <events/InputCodes.h>
#include <events/MouseEvent.h>
#include <events/KeyEvent.h>
#include <events/WindowEvent.h>
#include <graphics/renderables/Sprite2D.h>
#include <graphics/layers/Group.h>
#include <graphics/layers/Layer.h>
#include <graphics/BetterGL2DRenderer.h>
#include <math/math.h>
#include <utils/Logging.h>
#include <utils/Timer.h>
#include <graphics/cameras/FollowRenderableCamera.h>
#include <../ext/imgui/imgui.h>

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

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate() override;
    virtual void OnDraw() override;
    virtual void OnEvent(Event& e);
    virtual void OnImGuiRender() override;
};

#endif