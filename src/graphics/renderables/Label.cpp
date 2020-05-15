#include "Label.h"

Label::Label(std::string Text, float x, float y, KevFontInfo* font, Vec4f col)
    :  Renderable2D(Vec3f(x, y, 0), Vec2f(0, 0), col), font(font), text(Text)
{
}

void Label::Submit(KevRenderer* renderer)
{

    renderer->DrawString(text, position, font, color);

}
