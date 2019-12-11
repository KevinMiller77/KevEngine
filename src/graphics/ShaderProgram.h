#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <vector>
#include <string>

#include "GL/glew.h"

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

#include "../math/math.h"

GLint getShaderUniformLocation(GLint shaderProgramID, const GLchar* name);

void setShaderUniform1f(GLint shaderProgramID, const GLchar* name, float value);
void setShaderUniform1i(GLint shaderProgramID, const GLchar* name, int value);
void setShaderUniform2f(GLint shaderProgramID, const GLchar* name, const Vec2f& vector);
void setShaderUniform3f(GLint shaderProgramID, const GLchar* name, const Vec3f& vector);
void setShaderUniform4f(GLint shaderProgramID, const GLchar* name, const Vec4f& vector);
void setShaderUniformMat4(GLint shaderProgramID, const GLchar* name, const Mat4f& matrix);

void enableShaderProgram(GLint shaderProgramID);
void disableShaderProgram();

GLuint CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path);

#endif