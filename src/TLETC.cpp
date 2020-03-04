#include "TLETC.h"

TLETC::TLETC(Vec2u startScreenResolution)
{
    screenResolution = startScreenResolution;
    mousePos = Vec2u(0, 0);
}

//Call that happens every time the game starts
void TLETC::OnGameStart()
{
    timer.start();

    glClearColor(0.0f, 0.33f, 0.67f, 1.0f);

    ShaderProgram *shader = new ShaderProgram("../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");

    layerTile = new TileLayer(shader);

    layerTile->texture = new Texture("../textures/container.jpg");

    srand(time(NULL));

    float size_of_pixels = 1.0f;
    for (float y = 0.0f; y < 9.0f; y += size_of_pixels)
    {
        for (float x = 0.0; x < 16.0f; x += size_of_pixels)
        {
            layerTile->add(new Sprite(x, y, size_of_pixels, size_of_pixels, Vec4f(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));
        }
    }

    LOG_INF("Time to setup: %dms\n", (unsigned int)(timer.getTimePassedReset() * 1000));
}

//Code that is called directly before each frame is drawn
void TLETC::Draw()
{
    //End frame and display
    layerTile->render();

    //Let the timer know a frame passed
    timer.frameKeep();
}

void TLETC::Update()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    layerTile->getShader()->setUniform2f("light_pos", Vec2f(newX, newY));
}