#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>
#include <math.h>

#include <windows.h>
#include <wingdi.h>

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

struct GLMeshInfo {
    GLuint numVertices;
    GLuint numElements;
    GLuint vao;
    GLuint programID;
    GLenum drawMode;
};

void Win32Render(HDC windowHDC, GLMeshInfo meshInfo);
// NOTE(Adin): It's up to the platform layer to swap buffers becasue that
// varies between platforms
void GLRenderMesh(GLMeshInfo meshInfo);

#endif