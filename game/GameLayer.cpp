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
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    //Setup textures
    //textures.newTexture("crate", "resources/textures/container.jpg");
    //textures.newTexture("sponge","resources/textures/spongebob.jpg");
    textures.newTexture("morty", "resources/textures/morty.jpg", Vec2f(0.0f, 1.0f));
    textures.newTexture("dude", "resources/textures/KevDude.png");

    Group* background = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* text = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(-16.0f, 9.0f, 0.0f)));

    
    for (float x = 0.0f; x < 32.0f; x++)
    {
        for (float y = 0.0f; y < 18.0f; y++)
        {
           add(new Sprite(x, y, 0.9f, 0.9f, textures.getTexture("morty")));
        }
    }
    player = new Sprite(0, 0, 2.0f, 4.0f, textures.getTexture("dude")); 
    add(player);
    //camera.SetRenderable(player);

    pushTransform(new Mat4f(Mat4f::translation(Vec3f(-screenExtremes.x, -screenExtremes.y, 0.0f))));
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
        if (playerVelocity.x < 0)
        {
            playerVelocity.x += 2.0f * acceleration ;
        }
        else
        {
            playerVelocity.x = playerVelocity.x  + acceleration  <= maxAcceleration ? playerVelocity.x + acceleration : playerVelocity.x;
        }  
    }
    else if (Input::IsKeyPressed(KEV_KEY_A))
    {
        if (playerVelocity.x > 0)
        {
            playerVelocity.x -= 2.0f * acceleration ;
        }
        else
        {
            playerVelocity.x = playerVelocity.x - acceleration  >= -maxAcceleration ? playerVelocity.x - acceleration : playerVelocity.x;
        }
    }
    else
    {
        if (playerVelocity.x > 0)
        {
            playerVelocity.x = playerVelocity.x - 2 * acceleration  < 0 ? 0.0f : playerVelocity.x - 4 * acceleration ;
        }
        else
        {
            playerVelocity.x = playerVelocity.x + 2 * acceleration  > 0 ? 0.0f : playerVelocity.x + 4 * acceleration ;
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

        playerVelocity.y += 0.5 ;
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

    CollisionCheck();
}

void GameLayer::OnDraw()
{
    render();
}

void GameLayer::CollisionCheck()
{
    unsigned int numCollisions = 0;
    std::sort(renderables.begin(), renderables.end(), GameLayer::SortRenderables);
    std::vector<Renderable2D*> CurrentlyViewed;
    for (Renderable2D* renderable : renderables)
    {
        if (!renderable->IsSolid())
        {
            continue;
        }

        for (Renderable2D* second : CurrentlyViewed)
        {
            //LOG_INF("Got seconds\n");
            if (renderable->GetLeftBound() > second->GetRightBound())
            {
                //LOG_INF("X match\n");
                std::remove(CurrentlyViewed.begin(), CurrentlyViewed.end(), second);
                continue;
            }

            //Collision
            if (renderable->GetUpBound() > second->GetDownBound() && renderable->GetDownBound() > second->GetUpBound())
            {
                renderable->OnCollision(second);
                second->OnCollision(renderable);
                numCollisions++;
            }
        }

        CurrentlyViewed.push_back(renderable);
    }

    LOG_INF("%d Collisions\n", numCollisions);
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
    
    if (mouseYN < 0.5f) { mouseY = screenExtremes.y - screenExtremes.y * mouseYN * 2; }
    else { mouseY = -(screenExtremes.y * ((mouseYN - 0.5f) * 2)); }

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

/*
void GenerateKeyTest
{
    float yMin = 2.0f; float yMax = 4.5f; float xMin = 1.0f; float xMax = 15.0f;

    int cols = 0x10;
    int rows = 0xff / cols; 

    float xTerm = (xMax - xMin) / (float)cols;
    float yTerm = (yMax - yMin) / (float)rows;

    Vec2f sqSize = Vec2f(xTerm - xTerm / 10, yTerm - yTerm / 10);

    float curX = xMin;
    float curY = yMin;
    for (int x = 0; x < 0xff + 1; x ++)
    {
        if (x % 16 == 0)
        {
            curX = xMin;
            curY += 0.25;
        }
        keys[x] = new Sprite(curX, curY, sqSize.x, 0.225, Vec4f(0, 0, 0, 1));
        curX += xTerm;
    }
    int curKey = 0;
    for (float x = 1.0f; x < 15.0f; x += 14.0f / 18.0f)
    {
        mouse[curKey] = new Sprite(x, 8.0, 14.0f /18.0f - 1.4f / 18.0f, 0.5f, Vec4f(0, 0, 0, 1));
        curKey++;
    }

    for (int i = 0; i < 0xff + 1; i++)
    {
        if (i < 18)
        {
            //background->add(mouse[i]);
        }

        //background->add(keys[i]);
    }
}
*/