#include "TLETC.h"

TLETC::TLETC(Vec2u startScreenResolution)
{
    screenResolution = startScreenResolution;
    mousePos = Vec2u(0, 0);
}

//Call that happens every time the game starts
void TLETC::OnGameStart()
{
    // #BADA55
    glClearColor(0.729f, 0.854f, 0.333f, 1.0f);

    renderer = new GL2DRenderer();

    Mat4f ortho = Mat4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    GLuint programID = CreateGLProgram("../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    enableShaderProgram(programID);
    setShaderUniformMat4(programID, "pr_matrix", ortho);
    setShaderUniformMat4(programID, "ml_matrix", Mat4f::translation(Vec3f(0, 0, 0)));

    setShaderUniform2f(programID, "light_pos", Vec2f(4.0f, 1.5f));
    setShaderUniform4f(programID, "colour", Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

    sprites = new StaticSprite("Item1", programID, 2.0f, 2.0f, 1.0f, 2.0f, Vec4f(0.5f, 0.0f, 5.0f, 1.0f), "../textures/container.jpg");
    //sprites = new Renderable2D("Item1", Vec3f(2.0f, 2.0f, 0.0f), Vec2f(2.0f, 2.0f), Vec4f(0.5f, 0.0f, 5.0f, 1.0f), programID);

    renderer->submit(sprites);
}

//Code that is called directly before each frame is drawn
void TLETC::Draw(HDC windowHDC)
{
    LOG_INF("Drawing frame.\n");
    // Sample render function to show where to put rendering code
    Win32Render(windowHDC, renderer);
    LOG_INF("Frame drawn.\n");
}

void TLETC::Update()
{
    /*
    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    Vec3f newPos = Vec3f(newX - (sprites->getSize().x / 2), newY - (sprites->getSize().y / 2), 0.0f);
    sprites->setPosition(newPos);
    */
    renderer->submit(sprites);
}