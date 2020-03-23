#include <core/KevEngine.h>
#include "GameLayer.h"
#include "HUD.h"
#include <core/KevInput.h>

unsigned int LastFrameKeep = 0;
unsigned int LastUpdateKeep = 0;

class KevGame : public KevEngine
{
    Timer fps;
    Timer ups;
    Timer keyPressTimeout;

public:
    KevGame()
        : KevEngine(this)
    {
        Renderable2D::GameStart();
        fps.Start();
        ups.Start();
        keyPressTimeout.Start();

        window->SetVSync(1);

        //Set shader info
        shaders.NewShader("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
        shaders.Enable("basic");

        //Load in the texture coords for the shader
        int slots[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
        shaders.SetUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);

        PushOverlay(new GameLayer(window.get(), shaders.GetShader("basic").GetShaderID(), Vec2u(KEV_ENGINE_WINDOW_X, KEV_ENGINE_WINDOW_Y)));
        PushOverlay(new HUD(window.get(), shaders.GetShader("basic").GetShaderID()));
    }



    ~KevGame() override 
    {
        for (Layer* layer : LayerStack)
        {
            delete layer;
        }
    }

    void OnChildDraw()
    {
        unsigned int newFrames = fps.FrameKeep();
        if ( newFrames != 0)
        {
            LastFrameKeep = newFrames;
        }
    }

    void OnChildUpdate()
    {
        unsigned int newUpdate = ups.FrameKeep();
        if ( newUpdate != 0)
        {
            LastUpdateKeep = newUpdate;
        }
    }
};

KevEngine* CreateApplication()
{
    return new KevGame();
}