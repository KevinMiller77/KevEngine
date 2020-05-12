#include <core/KevEngine.h>
#include "GameLayer.h"
#include "HUD.h"
#include <core/KevInput.h>

class KevGame : public KevEngine
{

public:
    
    bool ReloadingShaders = false;
    Kev2DCamera* PlayerCam;
    Kev2DCamera* EditorCam;
    GameLayer* gameLayer;
    Timer keyTimer;
    
    KevGame()
        : KevEngine(this)
    {
        Renderable2D::GameStart();
        
        keyTimer.Start();
        
        window->SetVSync(1);
        PlayerCam = new Kev2DCamera(GAMESPACE_X, GAMESPACE_Y);
        PlayerCam->SetMovable(false);
        EditorCam = new Kev2DCamera(GAMESPACE_X, GAMESPACE_Y);

        //Set shader info
        shaders.NewShader("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
        shaders.Enable("basic");        
        
        //Load in the texture coords for the shader
        int slots[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
        
        shaders.SetUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);
        gameLayer = new GameLayer(window.get(), shaders.GetShader("basic").GetShaderID(), Vec2u(KEV_ENGINE_WINDOW_X, KEV_ENGINE_WINDOW_Y), PlayerCam);
    
        PushLayer(gameLayer);
        PushOverlay(new HUD(window.get(), shaders.GetShader("basic").GetShaderID(), PlayerCam));
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
        
        if (KevInput::IsKeyPressed(KeyCode::LeftBracket) && keyTimer.GetTimePassed() >= 0.5f)
        {
            if (gameLayer->IsPlaying())
            {
                gameLayer->SetPlaying(false);
                for (Layer* lay : EngLayerStack)
                {
                    lay->SetCamera(EditorCam);
                }
            }
            else
            {
                gameLayer->SetPlaying(true);
                for (Layer* lay : EngLayerStack)
                {
                    lay->SetCamera(PlayerCam);
                }
            }
            
            keyTimer.Reset();
        }
    }
};

KevEngine* CreateApplication()
{
    return new KevGame();
}
