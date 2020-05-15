#ifndef __RENDERER_2D__
#define __RENDERER_2D__

#define RENDERER_MAX_SPRITES 50000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICIES_SIZE (RENDERER_MAX_SPRITES * 6)

#define MAX_TEXTURE_SLOTS 16

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1
#define SHADER_TEXTURE_INDEX 2
#define SHADER_TEXTURE_ID_INDEX 3
#define SHADER_ML_MAT_INDEX 4

#include <graphics/KevRenderer.h>

class Renderer2D : public KevRenderer
{
public:
    virtual void Submit(Renderable2D *Renderable, const Vec2u TilesheetPos = Vec2u(0, 0)) override = 0;
    virtual void Draw() override = 0;
    virtual unsigned int DrawToBuffer() override = 0;
    virtual void DrawString(std::string text, Vec3f position, KevFontInfo* font, uint32_t color) override = 0;
    virtual void Begin(void* Shader = nullptr) override = 0;
    virtual void End() override = 0;

    static Renderer2D* Create(int* width, int* height);
    
private:
    virtual void Init() = 0;
};

#endif
