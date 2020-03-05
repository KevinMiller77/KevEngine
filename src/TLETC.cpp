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

    //Set shader info
    for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) texIDs[i] = i;
    shaderNames = new const char* [NUM_SHADERS] ({"basic"}); 
    shaders.newShader(shaderNames[0], "../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    shaders.enable(shaderNames[0]);
    shaders.setUniform1iv(shaderNames[0], "textures", texIDs, MAX_TEXTURE_SLOTS);

    //Setup textures
    textureNames = new const char* [NUM_TEXTURES]({"crate", "sponge", "geez"});
    textures.newTexture(textureNames[0], "../textures/container.jpg");
    textures.newTexture(textureNames[1], "../textures/spongebob.jpg");
    textures.newTexture(textureNames[2], "../textures/morty.jpg");

    layers.push_back(new TileLayer(shaders.getShaderPtr(shaderNames[0])->getShaderID()));
    layers.push_back(new TileLayer(shaders.getShaderPtr(shaderNames[0])->getShaderID()));

    srand(time(NULL));

    Group* background = new Group(Mat4f::translation(Vec3f(0.0f, 0.0f, 0.0f)));

    background->add(new Sprite(-1.0f, -1.0f, 0.0f, 0.0f, textures.getTexture(textureNames[0])));
    for (float y = 0.0f; y < 9.0f; y += 1.0f)
    {
        for (float x = 0.0; x < 16.0f; x += 1.0f)
        {
            if ((int)x % 2 == 0 ){
                background->add(new Sprite(x, y, 1.0f, 1.0f, textures.getTexture(textureNames[1])));
            }
            else {
                background->add(new Sprite(x, y, 1.0f, 1.0f, textures.getTexture(textureNames[0])));
            }


        }
    }

    layers[0]->add(background);

    
    Group* group = new Group(Mat4f::translation(Vec3f(2.0f, 2.0f, 0.0f)));
    group->add(new Sprite(0.0f, 0.0f, 5.0f, 5.0f, textures.getTexture(textureNames[1])));
    group->add(new Sprite(2.0f, 2.0f, 1.0f, 1.0f, textures.getTexture(textureNames[2])));

    layers[1]->add(group);

    LOG_INF("Time to setup: %dms\n", (unsigned int)(timer.getTimePassedReset() * 1000));
}

//Code that is called directly before each frame is drawn
void TLETC::Draw()
{
    //End frame and display
    for (Layer* layer : layers )
    {
        layer->render();
    }

    //Let the timer know a frame passed
    timer.frameKeep();
}

void TLETC::Update()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    shaders.enable(shaderNames[0]);
    shaders.setUniform2f(shaderNames[0], "light_pos", Vec2f(newX, newY));
}