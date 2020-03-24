#include "GameLayer.h"
#include <algorithm>
#include <fstream>
#include <iostream> 
#include <core/KevInput.h>

#include <glad/glad.h>


GameLayer::GameLayer(Window* Parent, unsigned int Shader, Vec2u ScreenSize, Vec2f ScreenExtremes)
    : Layer(Parent, new Kev2DRenderer((int*)Parent->GetWidthPtr(), (int*)Parent->GetHeightPtr()), Shader), screenSize(ScreenSize), screenExtremes(ScreenExtremes), camera(ScreenExtremes.x, ScreenExtremes.y)
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


    // We set the same viewport size (plus margin) to the next window (if first use)
    // ImGui::SetNextWindowSize(ImVec2(screenSize.x + 10, screenSize.y + 10));

    updateTime.Reset();
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double ts = updateTime.GetTimePassed();

    camera.OnUpdate();
    ShaderProgram::EnableShaderProgram(shader);
    ShaderProgram::SetShaderUniformMat4(shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());

    Vec3f curPlayerPos = player->GetPosition();


    if (KevInput::IsKeyPressed(KEV_KEY_D))
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
    else if (KevInput::IsKeyPressed(KEV_KEY_A))
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
    if (curPlayerPos.y + player->GetSize().y >= 17.99f)
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

    if (KevInput::IsKeyPressed(KEV_KEY_SPACE))
    {
        if (!jumping)
        {
            log.AddLog("Player jumped!\n");
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

    player->SetPosition(new Vec3f(newX, newY, 0.0f));
    
    updateTime.Reset();

    Manager.MouseCheck(mousePos);
    Manager.CollisionCheck();
}

void GameLayer::OnImGuiRender() 
{
    if (!IsImGuiEnabled())
    {
        return;
    }

    // ImGui::Begin("Game rendering");
    // ImVec2 pos = ImGui::GetCursorScreenPos();
    // ImGui::GetWindowDrawList()->AddImage(
    //     (void *)vpTexture, ImVec2(ImGui::GetItemRectMin().x + pos.x,
    //                         ImGui::GetItemRectMin().y + pos.y),
    //     ImVec2(pos.x + screenSize.x / 2, pos.y + screenSize.y / 2), ImVec2(0, 1), ImVec2(1, 0));
    // ImGui::End();

    ImGui::Begin("Player Params");
    ImGui::SliderFloat("Gravity Constant", &gravityConstant, 0.1, 5.0);
    ImGui::SliderFloat("Max Hori Accel", &maxAcceleration, 0.1, 5.0);
    ImGui::SliderFloat("Player Hori Accel", &acceleration, 0.1, 5.0);
    ImGui::SliderFloat("Max Jump Accel", &maxJumpAcceleration, 0.1, 5.0);
    ImGui::SliderFloat("Jump Accel", &jumpAcceleration, 0.1, 5.0);
    ImGui::SliderInt(  "Max Jump Presses", &maxJump, 1, 15);
    ImGui::SliderFloat("Key debounce interval (s)", &keyDebounceInterval, 0.05, 0.5);
    if (ImGui::Button( "Save player config\n"))
    {
        log.AddLog("Logging player settings\n");

        ofstream playerSettings;
        playerSettings.open("PlayerSettings.txt");

        playerSettings << "Gravity Constant " << gravityConstant << std::endl;
        playerSettings << "Max Hori Accel " << maxAcceleration << std::endl;
        playerSettings << "Player Hori Accel " << acceleration << std::endl;
        playerSettings << "Max Jump Accel " << maxJumpAcceleration << std::endl;
        playerSettings << "Jump Accel " << jumpAcceleration << std::endl;
        playerSettings << "Max Jump Presses " << maxJump << std::endl;
    
        playerSettings.close();
    }
    ImGui::End();

    log.Update(KevImGuiLogOpen);
}

void GameLayer::OnDraw()
{
    Render();
}

// void GameLayer::Render()
// {
//     if (enabled)
//     {
//         ShaderProgram::EnableShaderProgram(shader);
//         renderer->Begin();

//         for (Renderable2D *renderable : renderables)
//         {
//             renderable->Submit(renderer);
//         }
        
//         renderer->End();   
//         vpTexture = renderer->DrawToBuffer();
//     }
// }

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

bool GameLayer::KeyDown(KeyPressedEvent& e)
{
    if (keyDebounce.GetTimePassed() < keyDebounceInterval)
    {
        return false;
    }
    keyDebounce.Reset();

    KeyCode key = (KeyCode)(e.GetKeyCode());

    switch (key)
    {
        case(KEV_KEY_F3):
        {
            SetImGuiEnabled(!IsImGuiEnabled());
            break;
        }

        case(KEV_KEY_F11):
        {
            if (parent != nullptr) 
            {

                parent->ToggleFullscreen();
            }
            break;
        }

        case(KEV_KEY_V):
        {
            if (parent->IsVSync())
            {
                LOG_INF("Turning VSync off\n");
                parent->SetVSync(0);
            }
            else
            {
                LOG_INF("Turning VSync on\n");
                parent->SetVSync(1);
            }
            break;
        }

        default:
            break;
    }

    return true;
}

void GameLayer::OnEvent(Event& e)
{
    EventDispatcher dispatch(e);
    dispatch.Dispatch<MouseMovedEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseMove));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(GameLayer::WindowResize));
    dispatch.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseScroll));
    dispatch.Dispatch<KeyPressedEvent>(KEV_BIND_EVENT_FN(GameLayer::KeyDown));

    camera.OnEvent(e);

}