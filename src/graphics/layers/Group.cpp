#include "Group.h"

Group::Group(const Mat4f transform)
: ModelMatrix(transform)
{
}

void Group::add(Renderable2D* renderable)
{
    children.push_back(renderable);
}

void Group::submit(GL2DRenderer* renderer)
{
    renderer->push(ModelMatrix);
    for (const Renderable2D* renderable : children)
    {
        renderer->submit(renderable);
    }
    renderer->pop();
}