#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <vector>
#include <map>

#include "../utils/Logging.h"
#include "../utils/FileIO.h"

#include "../math/math.h"

class ShaderProgram {

private:
    unsigned int programID;

public:
    ShaderProgram() = default;
    ShaderProgram(const char* vertex_file_path, const char* fragment_file_path);


    static unsigned int CreateGLProgram(const char* vertex_file_path, const char* fragment_file_path);
    inline const unsigned int GetShaderID() const { return programID; }

    //There are two copies of all functions. We will want both static and non-static member functions to deal with shaders.
    void   SetUniform1f(const char* name, float value);
    void   SetUniform1fv(const char* name, float* value, int count);
    void   SetUniform1i(const char* name, int value);
    void   SetUniform1iv(const char* name, int* value, int count);
    void   SetUniform2f(const char* name, const Vec2f& vector);
    void   SetUniform3f(const char* name, const Vec3f& vector);
    void   SetUniform4f(const char* name, const Vec4f& vector);
    void   SetUniformMat4(const char* name, const Mat4f& matrix);

    unsigned int GetUniformLocation(const char* name);

    void   Enable();
    void   Disable();  


    static void   SetShaderUniform1f(unsigned int shaderProgramID, const char* name, float value);
    static void   SetShaderUniform1i(unsigned int shaderProgramID, const char* name, int value);
    static void   SetShaderUniform2f(unsigned int shaderProgramID, const char* name, const Vec2f& vector);
    static void   SetShaderUniform3f(unsigned int shaderProgramID, const char* name, const Vec3f& vector);
    static void   SetShaderUniform4f(unsigned int shaderProgramID, const char* name, const Vec4f& vector);
    static void   SetShaderUniformMat4(unsigned int shaderProgramID, const char* name, const Mat4f& matrix);

    static unsigned int GetShaderUniformLocation(unsigned int shaderProgramID, const char* name);

    static void   EnableShaderProgram(unsigned int shaderProgramID);
    static void   DisableShaderProgram();    
};
#endif