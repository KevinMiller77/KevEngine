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
    inline const GLuint GetShaderID() const { return programID; }

    //There are two copies of all functions. We will want both static and non-static member functions to deal with shaders.
    void   SetUniform1f(const GLchar* name, float value);
    void   SetUniform1fv(const GLchar* name, float* value, GLsizei count);
    void   SetUniform1i(const GLchar* name, int value);
    void   SetUniform1iv(const GLchar* name, int* value, GLsizei count);
    void   SetUniform2f(const GLchar* name, const Vec2f& vector);
    void   SetUniform3f(const GLchar* name, const Vec3f& vector);
    void   SetUniform4f(const GLchar* name, const Vec4f& vector);
    void   SetUniformMat4(const GLchar* name, const Mat4f& matrix);

    GLuint GetUniformLocation(const GLchar* name);

    void   Enable();
    void   Disable();  


    static void   SetShaderUniform1f(GLuint shaderProgramID, const GLchar* name, float value);
    static void   SetShaderUniform1i(GLuint shaderProgramID, const GLchar* name, int value);
    static void   SetShaderUniform2f(GLuint shaderProgramID, const GLchar* name, const Vec2f& vector);
    static void   SetShaderUniform3f(GLuint shaderProgramID, const GLchar* name, const Vec3f& vector);
    static void   SetShaderUniform4f(GLuint shaderProgramID, const GLchar* name, const Vec4f& vector);
    static void   SetShaderUniformMat4(GLuint shaderProgramID, const GLchar* name, const Mat4f& matrix);

    static GLuint GetShaderUniformLocation(GLuint shaderProgramID, const GLchar* name);

    static void   EnableShaderProgram(GLuint shaderProgramID);
    static void   DisableShaderProgram();    
};
#endif