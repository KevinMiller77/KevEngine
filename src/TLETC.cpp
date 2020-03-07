#include "TLETC.h"

TLETC::TLETC(Vec2u startScreenResolution)
{
    screenResolution = startScreenResolution;
    mousePos = Vec2u(0, 0);
    screenSize = Vec2f(16.0f, 9.0f);
    windowedMode = true;
}

//Call that happens every time the game starts
void TLETC::OnGameStart()
{
    Timer totalTime = Timer();
    totalTime.start();
    keyPressTimeout.start();

    //Set shader info
    for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) texIDs[i] = i;
    shaders.newShader("basic", "../shaders/SimpleVertexShader.glsl", "../shaders/SimpleFragShader.glsl");
    shaders.enable("basic");
    shaders.setUniform1iv("basic", "textures", texIDs, MAX_TEXTURE_SLOTS);

    //Setup textures
    textures.newTexture("crate", "../textures/container.jpg");
    textures.newTexture("sponge","../textures/spongebob.jpg");
    textures.newTexture("morty", "../textures/morty.jpg", Vec2f(0.0f, 1.0f));

    TileLayer* lay1 = new TileLayer(shaders.getShaderPtr("basic")->getShaderID());
    TileLayer* lay2 = new TileLayer(shaders.getShaderPtr("basic")->getShaderID());
    
    layers.push_back(lay1);
    layers.push_back(lay2);

    srand(time(NULL));

    Group* background = new Group(Mat4f::translation(Vec3f(-screenSize.x, -screenSize.y, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(0.0f, 0.0f, 0.0f)));

    background->add(new Sprite(-1.0f, -1.0f, 0.0f, 0.0f, textures.getTexture("crate")));
    for (float y = 0.0f; y < 9.0f; y += 0.5f)
    {
        for (float x = 0.0; x < 16.0f; x += 0.5f)
        {
            background->add(new Sprite(x, y, 0.5f, 0.5f, textures.getTexture("sponge")));
            swirly->add(new Sprite(x, y, 0.5f, 0.5f, textures.getTexture("morty")));
        }
    }
    
    layers[0]->add(background);
    layers[0]->pushTransform(&Mat4f::scale(Vec3f(2.0f, 2.0f, 0.0f)));
    
    layers[1]->add(swirly);
    layers[1]->pushTransform(&Mat4f::scale(Vec3f(2.0f, 2.0f, 0.0f)));
    
    layers[1]->pushTransform(&Mat4f::translation(Vec3f(-screenSize.x, -screenSize.y, 0.0f)));
    layers[1]->pushTransform(&Mat4f::rotation((int64_t)(timer.getTimeMS() / 10) % 360, Vec3f(0.0f, 0.0f, 1.0f)));

    unsigned int numToRender = background->getNumChildren();
    LOG_INF("Loaded %d Sprites to be renderered\n", numToRender);
    LOG_INF("Time to setup: %dms\n", (unsigned int)(totalTime.getTimePassedReset() * 1000));
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
    layers[1]->poptransform();

    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    shaders.enable("basic");
    shaders.setUniform2f("basic", "light_pos", Vec2f(newX, newY));

    if (layers.size() > 1) 
    {
        layers[1]->pushTransform(new Mat4f(Mat4f::rotation((int64_t)(timer.getTimeMS() / 10) % 360, Vec3f(0.0f, 0.0f, 1.0f))));

    }
}

void TLETC::ProcessInput(InputInformation in)
{
    switch(in._key)
    {
        case 0:
            break;

        //Number keys, 0-9
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: 
        case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
            if (keyPressTimeout.getTimePassed() >= KEY_DEBOUNCE_TIME) 
                break;
            
            if (layers.size() > in._key - 0x30)
                LOG_INF("Toggling layer %d\n", in._key - 0x30);
                layers[in._key - 0x30]->toggle();
            break;

        case 0x46: //F key, switches fullscreen
            if (keyPressTimeout.getTimePassed() >= KEY_DEBOUNCE_TIME) 
                break;
            
            windowedMode = toggleFullScreen();
            break;

        //R key
        case 0x52:  //R key, reloads entire program
            
            if (keyPressTimeout.getTimePassed() >= KEY_DEBOUNCE_TIME) 
                break;

            ResetEngine();
            OnGameStart();
            break;

        //up key
        case 0x26:
                break; 

        //down key
        case 0x28:
                break;
        default:
        LOG_INF("Undefined key pressed. Code: 0x%X\n", in._key);
            break;
    }
    if(in._key) keyPressTimeout.reset();

    if (((in._mousePos.x != 0) || (in._mousePos.y != 0)) && ((in._mousePos.x != mousePos.x) || (in._mousePos.y == mousePos.y))) 
    {

        if ((bool)(in._mouseButtons & 0x0010))
        {
            float newX = (float)screenSize.x * (((float)in._mousePos.x - (float)mousePos.x) / screenResolution.x);
            float newY = (float)screenSize.y * (((float)in._mousePos.y - (float)mousePos.y) / screenResolution.y);
            
            layers[0]->pushTransform(&Mat4f::translation(Vec3f(newX , newY, 0.0f)));
        }

        mousePos = in._mousePos;

        if (in._mouseWheelMag > 0)
        {
            LOG_INF("Zoom In\n");
            double magnitude = ((double)in._mouseWheelMag / ((double)in._mouseWheelMagConstant * 0xffff));
            layers[0]->pushTransform(&Mat4f::scale(Vec3f(1.0f + (magnitude * 0.1f) , 1.0f + (magnitude * 0.1f), 0.0f)));
        }
        else if (in._mouseWheelMag < 0)
        {
            LOG_INF("Zoom Out\n");
            double magnitude = (-(double)in._mouseWheelMag / ((double)in._mouseWheelMagConstant * 0xffff));
            layers[0]->pushTransform(&Mat4f::scale(Vec3f(1.0f / (1.0f + magnitude * 0.1f) , 1.0f / (1.0f + magnitude * 0.1f) , 0.0f)));
        }
    }
}

void TLETC::ResetEngine()
{
    timer.start();
    LOG_INF("Restarting engine\n");
    for (Layer* layer : layers)
        delete layer;
    layers.clear();
    
    shaders.disable("basic");
    shaders.clearShaders();
    textures.clearTextures();

    glFlush();
    if (restartContext != nullptr)
    {
        (*restartContext)();
    }

    
    LOG_INF("Time to reset: %dms\n", (unsigned int)(timer.getTimePassedReset() * 1000));
}

