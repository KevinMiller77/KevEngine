#include <core/KevEngine.h>
#include "GameLayer.h"
#include "HUD.h"

unsigned int LastFrameKeep = 0;
unsigned int LastUpdateKeep = 0;

class KevGame : public KevEngine
{
    Timer fps;
    Timer ups;
public:
    KevGame()
        : KevEngine(this)
    {
        Renderable2D::GameStart();
        fps.start();
        ups.start();
        //Set shader info
        shaders.newShader("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
        shaders.enable("basic");

        //Load in the texture coords for the shader
        int slots[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
        shaders.setUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);
        
        PushLayer(new GameLayer(shaders.getShader("basic").getShaderID(), Vec2u(window->GetWidth(), window->GetHeight())));
        PushOverlay(new HUD(shaders.getShader("basic").getShaderID()));
    }
    ~KevGame() override {}

    void OnChildDraw()
    {
        unsigned int newFrames = fps.frameKeep();
        if ( newFrames != 0)
        {
            LastFrameKeep = newFrames;
        }
    }

    void OnChildUpdate()
    {
        //LOG_INF("Numrenderablesglobal: %d", Renderable2D::GetGlobalNumRenderables());
        unsigned int newUpdate = ups.frameKeep();
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