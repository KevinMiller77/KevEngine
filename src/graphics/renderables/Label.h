#ifndef __LABEL__
#define __LABEL__

#include "Renderable2D.h"

class Label : public Renderable2D
{
private:
    std::string text;
    FontInfo* font;
    Vec3f pos;
    float x, y;

public:
    Label(std::string Text, float x, float y, FontInfo* font, Vec4f col);

    void Submit(KevRenderer* renderer) override;

    inline void SetText(std::string Text) { text = Text; }
    inline std::string GetText() { return text; }

};

#endif
