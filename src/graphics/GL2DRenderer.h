#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>
#include <math.h>

#include "../utils/Logging.h"
#include "../utils/FileIO.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "ShaderProgram.h"
#include "renderables/Renderable2D.h"

#include <deque>

class GL2DRenderer
{
protected:
    std::deque<const Renderable2D *> RenderQueue;

public:
    virtual void submit(const Renderable2D *renderable) = 0;
    virtual void draw() = 0;
    virtual void begin() = 0;
    virtual void end() = 0;
};

void Win32Render(HDC windowHDC, GL2DRenderer *renderer);

#endif