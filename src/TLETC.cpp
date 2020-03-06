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
    keyPressTimeout.start();

    //Set shader info
    for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) texIDs[i] = i;
    shaders.newShader("basic", "../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    shaders.enable("basic");
    shaders.setUniform1iv("basic", "textures", texIDs, MAX_TEXTURE_SLOTS);

    //Setup textures
    textures.newTexture("crate", "../textures/container.jpg");
    textures.newTexture("sponge", "../textures/spongebob.jpg");
    textures.newTexture("morty", "../textures/morty.jpg", Vec2f(0.0f, 1.0f));

    layers.push_back(new TileLayer(shaders.getShaderPtr("basic")->getShaderID()));
    layers.push_back(new TileLayer(shaders.getShaderPtr("basic")->getShaderID()));

    srand(time(NULL));

    Group* background = new Group(Mat4f::translation(Vec3f(0.0f, 0.0f, 0.0f)));

    background->add(new Sprite(-1.0f, -1.0f, 0.0f, 0.0f, textures.getTexture("crate")));
    for (float y = 0.0f; y < 9.0f; y += 0.05f)
    {
        for (float x = 0.0; x < 16.0f; x += 0.05f)
        {
            uint8_t m = rand() % 3;
            switch(m)
            {
                case(0): background->add(new Sprite(x, y, 0.1f, 0.1f, textures.getTexture("sponge"))); break;
                case(1): background->add(new Sprite(x, y, 0.1f, 0.1f, textures.getTexture("morty"))); break;
                case(2): background->add(new Sprite(x, y, 0.1f, 0.1f, textures.getTexture("crate"))); break;
            }
        }
    }
    unsigned int numToRender = background->getNumChildren();
    layers[0]->add(background);

    LOG_INF("Loaded %d Sprites to be renderered\n", numToRender);
    LOG_INF("Time to setup: %dms\n", (unsigned int)(timer.getTimePassedReset() * 1000));
}

//Code that is called directly before each frame is drawn
void TLETC::Draw()
{
    //End frame and display
    for (int i = 0; i < layers.size(); i++ )
    {
        Layer* layer = layers[i];
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

    shaders.enable("basic");
    shaders.setUniform2f("basic", "light_pos", Vec2f(newX, newY));
}

void TLETC::ProcessInput(InputInformation in)
{
    switch(in._key)
    {
        case 0:
            break;
        case 0x52:  //R key, reloads entire program
            
            if (keyPressTimeout.getTimePassed() > 0.5f)
            {
                ResetEngine();
                OnGameStart();
                keyPressTimeout.reset();
            }
            break;

        default:
            break;
    }

    if ((in._mousePos.x != 0.0f) || (in._mousePos.y != 0.0f))
    {
        mousePos = in._mousePos;
    }
}

void TLETC::ResetEngine()
{
    LOG_INF("Restarting engine\n");
    for (Layer* layer : layers)
        delete layer;
    layers.clear();
    
    shaders.disable("basic");
    shaders.clearShaders();
    textures.clearTextures();

    timer.reset();

    if (restartContext != nullptr)
    {
        (*restartContext)();
    }
}

