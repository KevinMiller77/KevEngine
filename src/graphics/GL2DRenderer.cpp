#include "GL2DRenderer.h"

#define USING_WINDOWS

#ifdef USING_WINDOWS
void Win32Render(HDC windowHDC, GL2DRenderer* renderer) {
    //Begin frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    renderer->draw();
    
    //End frame and display
    SwapBuffers(windowHDC);
}
#endif

void GL2DRenderer::submit(const Renderable2D* renderable)
{
    RenderQueue.push_back(renderable);
}

void GL2DRenderer::draw()
{
    while (!RenderQueue.empty())
    {
        const Renderable2D* renderable = RenderQueue.front();
        renderable->getVAO()->bind();
        renderable->getIBO()->bind();

        setShaderUniformMat4(renderable->getShaderID(), "ml_matrix", Mat4::translation(renderable->getPosition()));
        glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

        renderable->getIBO()->bind();
        renderable->getVAO()->bind();

        RenderQueue.pop_front();
    }
}
