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

    //Setup textures, can't be used without them
    textures.NewTexture("morty", "resources/textures/morty.jpg");
    textures.NewTexture("dude", "resources/textures/KevDude.png");

    scene = new Group(Mat4f::translation(Vec3f(-screenExtremes.x, -screenExtremes.y, 0.0f)));
    
    for (float x = 0; x < GAMESPACE_X * 2; x += 1)
    {
        for (float y = 0; y < GAMESPACE_Y * 2; y += 1)
        {
            scene->Add(new Sprite(x, y, 1, 1, textures.GetTexture("morty")));
        }
    }

    player = new PhysicsSprite(9, 16, 1.0f, 2.0f, textures.GetTexture("dude"), true);
    player->SetName("Kev");
    LOG_INF("Player pos: %f, %f\n", player->GetScreenPos().x, player->GetScreenPos().y); 
    scene->Add(player);
//    camera.SetRenderable(player);
    Add(scene);

    updateTime.Reset();
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate()
{
    if (paused)
    {
        return;
        updateTime.Reset();
    }
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double ts = 100 * updateTime.GetTimePassed();

    camera.OnUpdate();
    
    ShaderProgram::EnableShaderProgram(shader);
    ShaderProgram::SetShaderUniformMat4(shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());
    
    ImGuiIO io = ImGui::GetIO();
    
    if(!io.WantCaptureMouse)
    {
        Manager.MouseCheck(mousePos);
    }
    Manager.CollisionCheck();
    Manager.OnUpdate();
    
    //G ravity
    if (!player->IsStable())
    {
        player->AddMomentum(Vec3f(0.0f, 3.5f * ts, 0.0f));
    }
    else
    {
        if (KevInput::IsKeyPressed(KEV_KEY_SPACE))
        {
            player->AddMomentum(Vec3f(0.0f, -200, 0.0f));
        }
    }
    if (KevInput::IsKeyPressed(KEV_KEY_D))
    {
        player->AddMomentum(Vec3f(5.0f * ts, 0.0f, 0.0f));
    }
    if (KevInput::IsKeyPressed(KEV_KEY_A))
    {
        player->AddMomentum(Vec3f(-5.0f * ts, 0.0f, 0.0f));
    }

    updateTime.Reset();
}

void GameLayer::OnImGuiRender() 
{
    if (!IsImGuiEnabled())
    {
        return;
    }

    ImGui::Begin("Hello!");
    ImGui::Text("\t\tWelcome to the wonderful KevEngine!\n \
                The player has basic left and right movement controlled with A and D\n \
                He may also jump if you press SPACE\n \
                He is currently not a solid object but if you click him, he will turn pink and be solid\n \
                The above is also tru for the background tiles, you may make them solid by clicking them.\n \
                Now, when the player collides with the solid objects you will see them collide by turning blue.\n\n\n \
                That player ... he doesn't control so well. So, change it!!!\n \
                There is another tab in the gui block that will allow you to tune\n \
                the players movement parameters. Make it what you like, then save it with the button!\n \
                \n\n\n \
                Now, to the gui. It can dock an auto tab into other windows. It can leave the game window and everything.\n \
                Simply hold shift and drag around the windows!\n");
    ImGui::End();
    
    log.Update(KevImGuiLogOpen);
    
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

        case(KEV_KEY_P):
        {
            paused = !paused;
            LOG_INF("Game ");
            if (paused)
            {
                printf("unpaused\n");
            }
            else
            {
                printf("paused\n");
            }
            
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
