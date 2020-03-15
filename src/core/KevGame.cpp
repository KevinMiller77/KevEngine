#include "KevGame.h"

//Both equired for the interface with the OS.
//extern MemoryMetrics memoryTracker;
KevEngine* engine = new KevGame(SCREEN_SIZE_X, SCREEN_SIZE_Y);

//Call that happens every time the game starts
void KevGame::OnGameStart()
{
    //Reinstantiate memory monitor and set it to start
    //memoryTracker.track();

    //Enable blending of the alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Timer totalTime = Timer();
    totalTime.start();
    keyPressTimeout.start();

    fonts.add("arial", "fonts/arial.ttf", 32);
    fonts.add("inkfree", "fonts/INKFREE.ttf", 28);
    //fonts.add("cookie", "fonts/Cookie Cake Demo.otf", 28);

    //Set shader info
    shaders.newShader("basic", "shaders/SimpleVertexShader.glsl", "shaders/SimpleFragShader.glsl");
    shaders.enable("basic");


    //Load in the texture coords for the shader
    int slots[MAX_TEXTURE_SLOTS];
    for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
    shaders.setUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);

    //Setup textures
    textures.newTexture("crate", "textures/container.jpg");
    textures.newTexture("sponge","textures/spongebob.jpg");
    textures.newTexture("morty", "textures/morty.jpg", Vec2f(0.0f, 1.0f));

    TileLayer* lay1 = new TileLayer(shaders.getShaderPtr("basic")->getShaderID());
    TileLayer* lay2 = new TileLayer(shaders.getShaderPtr("basic")->getShaderID());
    TileLayer* lay3 = new TileLayer(shaders.getShaderPtr("basic")->getShaderID());
    
    layers.push_back(lay1); layers.push_back(lay2); layers.push_back(lay3);

    srand(time(NULL));

    Group* background = new Group(Mat4f::translation(Vec3f(-screenSize.x, -screenSize.y, 0.0f)));
    Group* textBox = new Group(Mat4f::translation(Vec3f(-screenSize.x + 0.3, -screenSize.y + 0.2, 0.0f)));
    Group* swirly = new Group(Mat4f::translation(Vec3f(-screenSize.x, screenSize.y, 0.0f)));

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

    layers[0]->add(background);
    layers[0]->pushTransform(new Mat4f(Mat4f::scale(Vec3f(2.0f, 2.0f, 0.0f))));
    
    textBox->add(new Sprite(0, 0, 5.0f, 1.5f, Vec4f(0.7f, 0.7f, 0.7f, 0.8f)));
    textBox->add(new Label(std::string("These r wrds"), 0.3f, 1.2f, fonts.get("arial"), Vec4f(1.0f, 1.0f, 1.0f, 1.0f)));

    layers[1]->add(textBox);

    layers[2]->add(swirly);

    unsigned int numToRender = background->getNumChildren();
    LOG_INF("Loaded %d Sprites to be renderered\n", numToRender);
    LOG_INF("Time to setup: %dms\n", (unsigned int)(totalTime.getTimePassedReset() * 1000));
    //LOG_INF("Heap allocations during setup: %d Bytes.\n", memoryTracker.doneTracking());

}

//Code that is called directly before each frame is drawn
void KevGame::Draw()
{
    //End frame and display
    for (Layer* layer : layers)
    {
        layer->render();
    }
    

    //Let the timer know a frame passed
    //timer.frameKeep();
}


void KevGame::OnTick()
{
    
}

void KevGame::OnUpdate()
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //layers[2]->poptransform();

    float newX = 16.0f * ((float)mousePos.x / screenResolution.x);
    float newY = 9.0f * ((float)mousePos.y / screenResolution.y);

    shaders.enable("basic");
    shaders.setUniform2f("basic", "light_pos", Vec2f(newX, newY));

    timer.frameKeep();
}

void KevGame::ProcessInput(InputInformation in)
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
            {
                LOG_INF("Toggling layer %d\n", in._key - 0x30);
                layers[in._key - 0x30]->toggle();
            }
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

        if ((bool)(in._mouseButtons & 0x0010) || (in._key == 0x11))
        {
            float newX = (float)screenSize.x * (((float)in._mousePos.x - (float)mousePos.x) / screenResolution.x);
            float newY = (float)screenSize.y * (((float)in._mousePos.y - (float)mousePos.y) / screenResolution.y);
            
            layers[0]->pushTransform(new Mat4f(Mat4f::translation(Vec3f(newX , newY, 0.0f))));
        }

        mousePos = in._mousePos;

        if (in._mouseWheelMag > 0)
        {
            LOG_INF("Zoom In\n");
            double magnitude = ((double)in._mouseWheelMag / ((double)in._mouseWheelMagConstant * 0xffff));
            layers[0]->pushTransform(new Mat4f(Mat4f::scale(Vec3f(1.0f + (magnitude * 0.1f) , 1.0f + (magnitude * 0.1f), 0.0f))));
        }
        else if (in._mouseWheelMag < 0)
        {
            LOG_INF("Zoom Out\n");
            double magnitude = (-(double)in._mouseWheelMag / ((double)in._mouseWheelMagConstant * 0xffff));
            layers[0]->pushTransform(new Mat4f(Mat4f::scale(Vec3f(1.0f / (1.0f + magnitude * 0.1f) , 1.0f / (1.0f + magnitude * 0.1f) , 0.0f))));
        }
    }
}

void KevGame::ResetEngine()
{
    LOG_INF("Restarting engine\n");
    
    //memoryTracker.track();

    timer.start();
    for (Layer* layer : layers)
        delete layer;
    layers.clear();
    
    shaders.clearShaders();
    textures.clearTextures();
    fonts.clearFonts();

    glFlush();
    if (restartContext != nullptr)
    {
        (*restartContext)();
    }

    LOG_INF("Time to reset: %dms\n", (unsigned int)(timer.getTimePassedReset() * 1000));
}