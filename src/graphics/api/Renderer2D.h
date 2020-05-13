#ifndef __RENDERER_2D__
#define __RENDERER_2D__

#include <graphics/KevRenderer.h>

class Renderer2D : public KevRenderer
{
public:
    virtual void Submit(Renderable2D *Renderable, const Vec2u TilesheetPos = Vec2u(0, 0)) override = 0;
    virtual void Draw() override = 0;
    virtual unsigned int DrawToBuffer() override = 0;
    virtual void DrawString(std::string text, Vec3f position, FontInfo* font, uint32_t color) override = 0;
    virtual void Begin(unsigned int Shader = 0) override = 0;
    virtual void End() override = 0;

    static Renderer2D* Create(int* width, int* height);
    
private:
    virtual void Init() = 0;
};

#endif
