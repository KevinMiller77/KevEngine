#include <core/KevEngine.h>
#include "GameLayer.h"
#include "HUD.h"
#include <core/KevInput.h>

class KevGame : public KevEngine
{

public:
    
    bool ReloadingShaders = false;
    
    KevGame()
        : KevEngine(this)
    {
        Renderable2D::GameStart();
        
        window->SetVSync(1);

        //Set shader info
        shaders.NewShader("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
        shaders.Enable("basic");

        //Load in the texture coords for the shader
        int slots[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
        shaders.SetUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);

        PushLayer(new GameLayer(window.get(), shaders.GetShader("basic").GetShaderID(), Vec2u(KEV_ENGINE_WINDOW_X, KEV_ENGINE_WINDOW_Y)));
//        PushOverlay(new HUD(window.get(), shaders.GetShader("basic").GetShaderID()));
    }



    ~KevGame() override 
    {
        
    }

    void OnGameDraw() override
    {
        
    }

    void OnGameUpdate() override
    {
        if (KevInput::IsKeyPressed(KEV_KEY_R) && !ReloadingShaders)
        {
            LOG_INF("Resetting Shaders\n");
            shaders.Disable("basic");
            shaders.Refresh("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
            shaders.Enable("basic");
            
            int slots[MAX_TEXTURE_SLOTS];
            for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
            shaders.SetUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);
            
            ReloadingShaders = true;
        }
        if (!KevInput::IsKeyPressed(KEV_KEY_R) && ReloadingShaders)
        {
            ReloadingShaders = false;
        }
    }
};

KevEngine* CreateApplication()
{
    return new KevGame();
}
