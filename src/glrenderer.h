#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>

struct GLMeshInfo {
    GLuint numVertices;
    GLuint numElements;
    GLuint vao;
    GLuint programID;
    GLenum drawMode;
};

GLMeshInfo GLRenderInit(char *vertexShaderLocation, char *fragmentShaderLocation);
// NOTE(Adin): It's up to the platform layer to swap buffers becasue that
// varies between platforms
void GLRender(GLMeshInfo meshInfo);

#endif