#include "Layer.h"

Layer::Layer(GL2DRenderer *renderer, ShaderProgram *shader, Mat4f projMatrix)
    : Renderer(renderer), Shader(shader), projectionMatrix(projMatrix)
{
    Shader->enable();
    Shader->setUniformMat4("pr_matrix", projectionMatrix);
    shader->setUniform2f("light_pos", Vec2f(4.0f, 1.5f));
}

Layer::~Layer()
{
    delete Shader;
    delete Renderer;

    for (int i = 0; i < renderables.size(); i++)
    {
        delete renderables[i];
    }
}

void Layer::add(Renderable2D *renderable)
{
    renderables.push_back(renderable);
}

void Layer::render()
{
    Shader->enable();
    Renderer->begin();

    for (const Renderable2D *renderable : renderables)
    {
        Renderer->submit(renderable);
    }

    Renderer->end();
    texture->bind();
    Renderer->draw();
    texture->unbind();
}
