#include "Group.h"

Group::Group(const Mat4f transform)
: ModelMatrix(transform)
{
}

void Group::add(Renderable2D* renderable)
{
    children.push_back(renderable);
}

void Group::submit(Renderer2D* renderer) const
{
    renderer->push(ModelMatrix);
    for (const Renderable2D* renderable : children)
    {
        renderable->submit(renderer);
    }
    renderer->pop();
}