#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <vector>
#include <map>

#include "GL/glew.h"

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

#include "../math/math.h"

class ShaderProgram {

private:
    GLuint programID;

public:
    ShaderProgram() = default;
    ShaderProgram(const char* vertex_file_path, const char* fragment_file_path);


    static GLuint CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path);
    inline const GLuint getShaderID() const { return programID; }

    //There are two copies of all functions. We will want both static and non-static member functions to deal with shaders.
    void   setUniform1f(const GLchar* name, float value);
    void   setUniform1fv(const GLchar* name, float* value, GLsizei count);
    void   setUniform1i(const GLchar* name, int value);
    void   setUniform1iv(const GLchar* name, int* value, GLsizei count);
    void   setUniform2f(const GLchar* name, const Vec2f& vector);
    void   setUniform3f(const GLchar* name, const Vec3f& vector);
    void   setUniform4f(const GLchar* name, const Vec4f& vector);
    void   setUniformMat4(const GLchar* name, const Mat4f& matrix);

    GLuint getUniformLocation(const GLchar* name);

    void   enable();
    void   disable();  


    static void   setShaderUniform1f(GLuint shaderProgramID, const GLchar* name, float value);
    static void   setShaderUniform1i(GLuint shaderProgramID, const GLchar* name, int value);
    static void   setShaderUniform2f(GLuint shaderProgramID, const GLchar* name, const Vec2f& vector);
    static void   setShaderUniform3f(GLuint shaderProgramID, const GLchar* name, const Vec3f& vector);
    static void   setShaderUniform4f(GLuint shaderProgramID, const GLchar* name, const Vec4f& vector);
    static void   setShaderUniformMat4(GLuint shaderProgramID, const GLchar* name, const Mat4f& matrix);

    static GLuint getShaderUniformLocation(GLuint shaderProgramID, const GLchar* name);

    static void   enableShaderProgram(GLuint shaderProgramID);
    static void   disableShaderProgram();    
};
#endif