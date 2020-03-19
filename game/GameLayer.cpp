#include "GameLayer.h"
#include <core/Core.h>

#include <algorithm>
#include <iostream> 


GameLayer::GameLayer(unsigned int shader, Vec2u screensize, Vec2f screenextremes)
    : Layer(new BetterGL2DRenderer(), shader), screenSize(screensize), screenExtremes(screenextremes), camera(screenExtremes.x, screenExtremes.y)
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
    updateTime.Reset();

    //Setup textures
    //textures.newTexture("crate", "resources/textures/container.jpg");
    //textures.NewTexture("sponge","resources/textures/spongebob.jpg");
    textures.NewTexture("morty", "resources/textures/morty.jpg");
    textures.NewTexture("dude", "resources/textures/KevDude.png");

    Group* background = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* text = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(-16.0f, 9.0f, 0.0f)));

    
    for (float x = 0.0f; x < 32.0f; x++)
    {
        for (float y = 0.0f; y < 18.0f; y++)
        {
            background->Add(new Sprite(x, y, 1, 1, textures.GetTexture("morty")));
        }
    }


    player = new Sprite(0, 0, 2.0f, 4.0f, textures.GetTexture("dude")); 
    background->Add(player);
    //camera.SetRenderable(player);
    Add(background);

    updateTime.Reset();
}

void GameLayer::OnDetatch()
{

}

void GameLayer::OnUpdate()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double ts = updateTime.GetTimePassed();

    camera.OnUpdate();
    ShaderProgram::EnableShaderProgram(Shader);
    ShaderProgram::SetShaderUniformMat4(Shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());

    Vec3f curPlayerPos = player->GetPosition();

    if (Input::IsKeyPressed(KEV_KEY_D))
    {
        if (playerVelocity.x < 0)
        {
            playerVelocity.x += 2.0f * acceleration * ts;
        }
        else
        {
            playerVelocity.x = playerVelocity.x  + acceleration * ts <= maxAcceleration ? playerVelocity.x + acceleration * ts: playerVelocity.x;
        }  
    }
    else if (Input::IsKeyPressed(KEV_KEY_A))
    {
        if (playerVelocity.x > 0)
        {
            playerVelocity.x -= 2.0f * acceleration * ts;
        }
        else
        {
            playerVelocity.x = playerVelocity.x - acceleration * ts >= -maxAcceleration ? playerVelocity.x - acceleration * ts: playerVelocity.x;
        }
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
    if (curPlayerPos.y + player->GetSize().y >= 17.95f)
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

        playerVelocity.y += gravityConstant * ts;
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

        if (jumpCount < maxJump)
        {
            playerVelocity.y = playerVelocity.y - jumpAcceleration  < -maxJumpAcceleration ? 0 : playerVelocity.y - jumpAcceleration ;
        }
    }

    float newX = curPlayerPos.x + playerVelocity.x;
    float newY = curPlayerPos.y + playerVelocity.y;

    if (newX > 32.0f - player->GetSize().x)
    {
        newX = 32.0f - player->GetSize().x;
    } else if (newX < 0.0f)
    {
        newX = 0.0f;
    }
    if (newY > 18.0f - player->GetSize().y)
    {
        newY = 18.0f - player->GetSize().y;
    } else if (newY < 0.0f)
    {
        newY = 0.0f;
    }

    player->SetPosition(Vec3f(newX, newY, 0.0f));
    
    updateTime.Reset();

    Manager.MouseCheck(mousePos);
    Manager.CollisionCheck();
}

void GameLayer::OnDraw()
{
    Render();
}

bool GameLayer::MouseScroll(MouseScrolledEvent& e)
{
    e.Handle();
    return false;
}

bool GameLayer::MouseMove(MouseMovedEvent& e)
{
    float mouseX, mouseY;
    float mouseXN = (float) e.getPos().x / (float) screenSize.x;
    float mouseYN = (float) e.getPos().y / (float) screenSize.y;

    if (mouseXN < 0.5f) { mouseX = -screenExtremes.x + screenExtremes.x * mouseXN * 2; }
    else { mouseX = screenExtremes.x * (mouseXN - 0.5f) * 2; }
    
    if (mouseYN < 0.5f) { mouseY = -screenExtremes.y + screenExtremes.y * mouseYN * 2; }
    else { mouseY = screenExtremes.y * ((mouseYN - 0.5f) * 2); }

    mousePos = Vec2f(mouseX, mouseY);

    return false;
}

bool GameLayer::WindowResize(WindowResizeEvent& e)
{
    screenSize = e.getScreenSize();
    return false;
}

void GameLayer::OnEvent(Event& e)
{
    EventDispatcher dispatch(e);
    dispatch.Dispatch<MouseMovedEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseMove));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(GameLayer::WindowResize));
    dispatch.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseScroll));

    camera.OnEvent(e);

}