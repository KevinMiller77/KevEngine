#include "GameLayer.h"
#include <core/Input.h>
#include <core/events/WindowsInputCodes.h>
#include <iostream> 
#include <algorithm>


GameLayer::GameLayer(unsigned int shader)
    : Layer(new BetterGL2DRenderer(), shader), camera(16.0f, 9.0f)
{
    //Enable blending of the alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GameLayer::~GameLayer()
{
    for (Renderable2D* renderable : renderables)
    {
        delete renderable;
    }

}

void GameLayer::OnAttach()
{
    //Setup textures
    textures.newTexture("crate", "resources/textures/container.jpg");
    textures.newTexture("sponge","resources/textures/spongebob.jpg");
    textures.newTexture("morty", "resources/textures/morty.jpg", Vec2f(0.0f, 1.0f));
    textures.newTexture("dude", "resources/textures/KevDude.jpg");

    Group* background = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* textBox = new Group(Mat4f::translation(Vec3f(-16.0f + 0.3f, -9.0f + 0.2f, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(-16.0f, 9.0f, 0.0f)));

    background->add(new Sprite(-19.0f, -10.0f, 0.0f, 0.0f, Vec4f(0.0f, 0.0f, 0.0f, 0.0f)));
    for (float y = 0.0f; y < 18.0f; y ++)
    {
        for (float x = 0.0; x < 32.0f; x ++)
        {
            background->add(new Sprite(x, y, 1, 1, textures.getTexture("sponge")));
            //background->add(new Sprite(x, y, 0.5f, 0.5f, Vec4f(0.7f, 1.0f, 1.0f, 0.5f)));
        }
    }

    player = new Sprite(16 - 1, 9 - 2, 2.0f, 4.0f, textures.getTexture("dude")); 
    background->add(player);
    //camera.SetRenderable(player);

    //pushTransform(new Mat4f(Mat4f::scale(Vec3f(2.0f, 2.0f, 0.0f))));
    add(background);

    updateTime.reset();
}

void GameLayer::OnDetatch()
{

}

void GameLayer::OnUpdate()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double ts = updateTime.getTimePassed();

    camera.OnUpdate();
    ShaderProgram::enableShaderProgram(Shader);
    ShaderProgram::setShaderUniformMat4(Shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());

    Vec3f curPlayerPos = player->getPosition();

    if (Input::IsKeyPressed(KEV_KEY_D))
    {
        if (playerVelocity.x < 0) playerVelocity.x = 0;
        playerVelocity.x = playerVelocity.x  + acceleration * ts <= maxAcceleration ? playerVelocity.x + acceleration * ts: playerVelocity.x;
    }
    else if (Input::IsKeyPressed(KEV_KEY_A))
    {
        if (playerVelocity.x > 0) playerVelocity.x = 0;
        playerVelocity.x = playerVelocity.x - acceleration * ts >= -maxAcceleration ? playerVelocity.x - acceleration * ts: playerVelocity.x;
    }
    else
    {
        if (playerVelocity.x > 0)
        {
            playerVelocity.x = playerVelocity.x - 2 * acceleration * ts < 0 ? 0.0f : playerVelocity.x - 4 * acceleration * ts;
        }
        else
        {
            playerVelocity.x = playerVelocity.x + 2 * acceleration * ts > 0 ? 0.0f : playerVelocity.x + 4 * acceleration * ts;
        }
    }

    //On ground
    if (curPlayerPos.y + player->getSize().y >= 17.95f)
    {
        //Is the first time ive been here
        if (!onGround)
        {
            playerVelocity.y = 0;
            onGround = true;
            jumping = false;
            jumpCount = 0;
        }
    }
    else
    {
        if (onGround)
        {
            onGround = false;

        }

        playerVelocity.y += 0.5 * ts;
    }

    if (Input::IsKeyPressed(KEV_KEY_SPACE))
    {
        if (!jumping)
        {
            jumping = true;
        }

        if (jumping)
        {
            jumpCount++;
        }

        if (jumpCount < 50)
        {
            playerVelocity.y = playerVelocity.y - 1.5f * ts < -maxJumpAcceleration ? 0 : playerVelocity.y - 1.5f * ts;
        }
    }

    float newX = curPlayerPos.x + playerVelocity.x;
    float newY = curPlayerPos.y + playerVelocity.y;

    if (newX > 32.0f - player->getSize().x)
    {
        newX = 32.0f - player->getSize().x;
    } else if (newX < 0.0f)
    {
        newX = 0.0f;
    }
    if (newY > 18.0f - player->getSize().y)
    {
        newY = 18.0f - player->getSize().y;
    } else if (newY < 0.0f)
    {
        newY = 0.0f;
    }

    player->setPosition(Vec3f(newX, newY, 0.0f));
    
    updateTime.reset();
}

void GameLayer::OnDraw()
{
    render();
}

bool GameLayer::MouseScroll(MouseScrolledEvent& e)
{
    e.Handle();
    return true;
}



void GameLayer::OnEvent(Event& e)
{
    EventDispatcher dispatch(e);
    dispatch.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseScroll));

    camera.OnEvent(e);
}