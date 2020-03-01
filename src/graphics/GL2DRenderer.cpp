#include "GL2DRenderer.h"

#define USING_WINDOWS

#ifdef USING_WINDOWS
void Win32Render(HDC windowHDC, GL2DRenderer *renderer)
{
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    LOG_INF("Inner frame draw.\n");
    renderer->draw();

    //End frame and display
    SwapBuffers(windowHDC);
}
#endif

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
