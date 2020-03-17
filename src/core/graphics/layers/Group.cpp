#include "Group.h"

Group::Group(const Mat4f transform)
: ModelMatrix(transform)
{
    Vec4f base = transform * Vec4f(1, 1, 1, 1);
    baseOrigin = new Vec3f(base.x - 1.0f, base.y - 1.0f, base.z - 1.0f);
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