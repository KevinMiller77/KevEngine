#include "Layer.h"

Layer::Layer(GL2DRenderer *renderer, ShaderProgram *shader, Mat4f projMatrix)
    : Renderer(renderer), Shader(shader), projectionMatrix(projMatrix)
{
    texture = new Texture();
    Shader->enable();
    Shader->setUniformMat4("pr_matrix", projectionMatrix);
    Shader->disable();
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

    for (Renderable2D *renderable : renderables)
    {
        renderable->submit(Renderer);
    }

    Renderer->end();   
    Renderer->draw();
}
