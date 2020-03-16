#include "GameLayer.h"
#include <core/Input.h>
#include <core/events/WindowsInputCodes.h>


GameLayer::GameLayer(unsigned int shader)
    : Layer(new BetterGL2DRenderer(), shader), camera(OrthographicCameraController(1280.0f / 720.0f, true))
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
    fonts.add("arial", "resources/fonts/arial.ttf", 32);
    fonts.add("inkfree", "resources/fonts/INKFREE.ttf", 28);
    //fonts.add("cookie", "fonts/Cookie Cake Demo.otf", 28);

    //Setup textures
    textures.newTexture("crate", "resources/textures/container.jpg");
    textures.newTexture("sponge","resources/textures/spongebob.jpg");
    textures.newTexture("morty", "resources/textures/morty.jpg", Vec2f(0.0f, 1.0f));

    Group* background = new Group(Mat4f::translation(Vec3f(-16.0f, -9.0f, 0.0f)));
    Group* textBox = new Group(Mat4f::translation(Vec3f(-16.0f + 0.3f, -9.0f + 0.2f, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(-16.0f, 9.0f, 0.0f)));

    background->add(new Sprite(-19.0f, -10.0f, 0.0f, 0.0f, Vec4f(0.0f, 0.0f, 0.0f, 0.0f)));
    for (float y = 0.0f; y < 9.0f; y += 0.5f)
    {
        for (float x = 0.0; x < 16.0f; x += 0.5f)
        {
            background->add(new Sprite(x, y, 0.5f, 0.5f, textures.getTexture("sponge")));
            //background->add(new Sprite(x, y, 0.5f, 0.5f, Vec4f(0.7f, 1.0f, 1.0f, 0.5f)));
            if ((int)x % 1 == 0) swirly->add(new Sprite(x, y, 0.5f, 0.5f, textures.getTexture("crate")));
        }
    }

    pushTransform(new Mat4f(Mat4f::scale(Vec3f(2.0f, 2.0f, 0.0f))));
    add(background);
}

void GameLayer::OnDetatch()
{

}

void GameLayer::OnUpdate()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Input::IsKeyPressed(KEV_KEY_R))
    {
        LOG_INF("R Pressed\n");
    }

    camera.OnUpdate();
    ShaderProgram::enableShaderProgram(Shader);
    ShaderProgram::setShaderUniformMat4(Shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());
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