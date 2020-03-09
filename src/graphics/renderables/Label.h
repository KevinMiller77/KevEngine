#ifndef __LABEL__
#define __LABEL__

#include "Renderable2D.h"

class Label : public Renderable2D
{
private:
    std::string text;
    Vec3f pos;
    float x, y;

public:
    Label(std::string Text, float x, float y, Vec4f col);

    void submit(Renderer2D* renderer) const override;

    inline void setText(std::string Text) { text = Text; }
    inline std::string getText() { return text; }
};

#endif