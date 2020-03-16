#include <core/KevEngine.h>
#include "GameLayer.h"

class KevGame : public KevEngine
{
public:
    KevGame()
    {
        //Set shader info
        shaders.newShader("basic", "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragShader.glsl");
        shaders.enable("basic");

        //Load in the texture coords for the shader
        int slots[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; i++) { slots[i] = i; }
        shaders.setUniform1iv("basic", "textures", slots, MAX_TEXTURE_SLOTS);
        
        PushLayer(new GameLayer(shaders.getShader("basic").getShaderID()));
    }
    ~KevGame() override {}

};

KevEngine* CreateApplication()
{
    return new KevGame();
}