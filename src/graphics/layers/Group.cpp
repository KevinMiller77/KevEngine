#include "Group.h"

Group::Group(const Mat4f transform)
: ModelMatrix(transform)
{
    type = RenderableType::Group;
    SolidObject = false;
    singleItem = false;
    baseOrigin = new Vec3f(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);
}

void Group::Add(Renderable2D* renderable)
{
    children.push_back(renderable);
    if (renderable->GetBase() == nullptr)
    {
        renderable->SetBase(baseOrigin);
    }
    else
    {
        Vec3f curBase = *renderable->GetBase();
        renderable->SetBase(new Vec3f(curBase.x + baseOrigin->x, curBase.y + baseOrigin->y, curBase.z + baseOrigin->z));
    }
}

void Group::Submit(GL2DRenderer* renderer) const
{
    renderer->Push(ModelMatrix);
    for (const Renderable2D* renderable : children)
    {
        renderable->Submit(renderer);
    }
    renderer->Pop();
}

void Group::CheckCollision(Renderable2D* other)
{
    
}

void Group::MouseCheck(Vec2f& mousePos, std::vector<Renderable2D*>& underMouse)
{
    for (int i = children.size() - 1; i >= 0; i--)
    {
        children[i]->MouseCheck(mousePos, underMouse);
    }
}