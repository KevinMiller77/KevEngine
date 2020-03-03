#include "TLETC.h"

TLETC::TLETC(Vec2u startScreenResolution)
{
    screenResolution = startScreenResolution;
    mousePos = Vec2u(0, 0);
    frameCount = 0;
}

std::vector<Renderable2D *> sprites;

//Call that happens every time the game starts
void TLETC::OnGameStart()
{
    timer.reset();

    Mat4f ortho = Mat4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    shader = ShaderProgram("../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    shader.enable();
    shader.setUniformMat4("pr_matrix", ortho);

    srand(time(NULL));

    GLuint num_sprite = 0;
    float x_size = 0.05f;
    float y_size = 0.05f;

    for (float y = 0.0f; y < 9.0f; y += y_size)
    {
        for (float x = 0.0; x < 16.0f; x += x_size)
        {
            sprites.push_back(new Renderable2D(Vec3f(x, y, 0), Vec2f(x_size, y_size), Vec4f(1.0f, 1.0f, 1.0f, 1.0f)));
            sprites[num_sprite]->setColor(Vec4f(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f));
            num_sprite++;
        }
    }

    renderer = new BetterGL2DRenderer();

    shader.setUniform2f("light_pos", Vec2f(4.0f, 1.5f));
    shader.setUniform4f("colour", Vec4f(0.0f, 0.3f, 0.8f, 1.0f));

    LOG_INF("Time to setup: %fms\n", timer.getTimePassedReset());
}

//Code that is called directly before each frame is drawn
void TLETC::Draw()
{
    //End frame and display
    renderer->draw();

    frameCount++;

    if (timer.getTimePassed() >= 1)
    {
        LOG_INF("FPS: %d\n", frameCount);
        timer.reset();
        frameCount = 0;
    }
}

void TLETC::Update()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    shader.setUniform2f("light_pos", Vec2f(newX, newY));

    renderer->begin();

    for (int i = 0; i < sprites.size(); i++)
    {
        //sprites[i]->setColor(Vec4f(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f));
        renderer->submit(sprites[i]);
    }

    renderer->end();
}