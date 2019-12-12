#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <vector>
#include <string>

#include "GL/glew.h"

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

#include "../math/math.h"

GLuint getShaderUniformLocation(GLuint shaderProgramID, const GLchar* name);

void setShaderUniform1f(GLuint shaderProgramID, const GLchar* name, float value);
void setShaderUniform1i(GLuint shaderProgramID, const GLchar* name, int value);
void setShaderUniform2f(GLuint shaderProgramID, const GLchar* name, const Vec2& vector);
void setShaderUniform3f(GLuint shaderProgramID, const GLchar* name, const Vec3& vector);
void setShaderUniform4f(GLuint shaderProgramID, const GLchar* name, const Vec4& vector);
void setShaderUniformMat4(GLuint shaderProgramID, const GLchar* name, const Mat4& matrix);

void enableShaderProgram(GLuint shaderProgramID);
void disableShaderProgram();

GLuint CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path);

#endif