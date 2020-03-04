#ifndef __GL_2D_RENDERER__
#define __GL_2D_RENDERER__

#include "GL2DRenderer.h"

#if 0

//This code is disabled due to the implementation of Renderable2D being changed
void GL2DRenderer::submit(const Renderable2D *renderable)
{
    RenderQueue.push_back(renderable);
}

void GL2DRenderer::draw()
{
    while (!RenderQueue.empty())
    {
        LOG_INF("Render->draw()\n");
        const Renderable2D *renderable = RenderQueue.front();
        LOG_INF("Before tex analysis\n");
        if (renderable->getTexturePtr() != nullptr)
        {
            glBindTexture(GL_TEXTURE_2D, renderable->getTextureID());
        }
        else
        {
            LOG_INF("Drawing object without texture.\n");
        }
        renderable->getVAO()->bind();
        renderable->getIBO()->bind();

        setShaderUniformMat4(renderable->getShaderID(), "ml_matrix", Mat4f::translation(renderable->getPosition()));
        glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

        renderable->getIBO()->unbind();
        renderable->getVAO()->unbind();

        RenderQueue.pop_front();
    }
}

#endif
#endif