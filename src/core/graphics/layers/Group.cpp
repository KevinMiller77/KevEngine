#include "Group.h"

Group::Group(const Mat4f transform)
: ModelMatrix(transform)
{
    type = GroupType;
    Vec4f base = transform * Vec4f(1, 1, 1, 1);
    baseOrigin = new Vec3f(base.x - 1.0f, base.y, base.z - 1.0f);
}

void Group::add(Renderable2D* renderable)
{
    children.push_back(renderable);
    renderable->SetBase(baseOrigin);
}

void Group::submit(GL2DRenderer* renderer) const
{
    renderer->push(ModelMatrix);
    for (const Renderable2D* renderable : children)
    {
        renderable->submit(renderer);
    }
    renderer->pop();
}

bool Group::IsColliding(Renderable2D* other)
{
    bool hadOne = false;
    for (Renderable2D* child : children)
    {
        child->IsColliding(other);
        for (Renderable2D* child2 : children);
    }

    return hadOne;
}

void Group::MouseCheck(Vec2f& mousePos)
{
    for (Renderable2D* child : children)
    {
        child->MouseCheck(mousePos);
    }
}