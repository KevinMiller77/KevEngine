#ifndef __GL_RENDERER_H__
#define __GL_RENDERER_H__

#include <GL/glew.h>

struct GLMeshInfo {
    GLuint numVertices;
    GLuint vao;
    GLuint programID;
    GLenum drawMode;
};

GLMeshInfo GLRenderInit(char *vertexShaderLocation, char *fragmentShaderLocation);
void GLRender(GLMeshInfo meshInfo);

#endif