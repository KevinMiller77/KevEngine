#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>

struct GLMeshInfo {
    GLuint numVertices;
    GLuint numElements;
    GLuint vao;
    GLuint programID;
    GLenum drawMode;
    GLuint rotAngleLoc; // TODO(Adin): make uniform storage more generic
};

GLMeshInfo GLRenderInit(char *vertexShaderLocation, char *fragmentShaderLocation);
// NOTE(Adin): It's up to the platform layer to swap buffers becasue that
// varies between platforms
void GLRenderMesh(GLMeshInfo meshInfo);

#endif