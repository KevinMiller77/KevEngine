#include "Label.h"

Label::Label(std::string Text, float x, float y, Vec4f col)
    :  Renderable2D(Vec3f(x, y, 0), Vec2f(0, 0), col), text(Text)
{
}

void Label::submit(Renderer2D* renderer) const
{

    renderer->drawString(text, position, color);

}