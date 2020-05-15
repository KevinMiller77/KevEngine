#ifndef __METAL_SHADER_PROGRAM__
#define __METAL_SHADER_PROGRAM__

#include <vector>
#include <map>

#include <utils/Logging.h>
#include <utils/FileIO.h>

#include <math/math.h>
#include <platform/graphics/Metal/Metal.h>
#include <graphics/api/ShaderProgram.h>

class MetalShaderProgram : public ShaderProgram
{
private:
    id<MTLRenderPipelineState> m_Shader;

public:
    MetalShaderProgram(const char* vertex_file_name, const char* fragment_file_name);
    inline virtual void* GetShader() override { return &m_Shader; }

    //WARN:: FOR METAL SHADERS, YOU MUST GIVE AN INTEGER INDEX FOR THE UNI NOT A STRING
//    static unsigned int CreateMetalProgram(const char* vertex_file_path, const char* fragment_file_path);
//    unsigned int RefreshMetalProgram(const char* vertex_file_path, const char* fragment_file_path);
//
//    //There are two copies of all functions. We will want both static and non-static member functions to deal with shaders.
//    void   SetUniform1f(const char*  ID, float value);
//    void   SetUniform1fv(const char* ID, float* value, int count);
//    void   SetUniform1i(const char*  ID, int value);
//    void   SetUniform1iv(const char* ID, int* value, int count);
//    void   SetUniform2f(const char*  ID, const Vec2f& vector);
//    void   SetUniform3f(const char*  ID, const Vec3f& vector);
//    void   SetUniform4f(const char*  ID, const Vec4f& vector);
//    void   SetUniformMat4(const char* ID, const Mat4f& matrix);
//
//    unsigned int GetUniformLocation(const char* ID);
//
    void   Enable() {};
    void   Disable() {};
//
//
//    static void   SetShaderUniform1f(void* Shader, const char* ID, float value);
//    static void   SetShaderUniform1i(void* Shader, const char* ID, int value);
//    static void   SetShaderUniform2f(void* Shader, const char* ID, const Vec2f& vector);
//    static void   SetShaderUniform3f(void* Shader, const char* ID, const Vec3f& vector);
//    static void   SetShaderUniform4f(void* Shader, const char* ID, const Vec4f& vector);
//    static void   SetShaderUniformMat4(void* Shader, const char* ID, const Mat4f& matrix);
//
//    static unsigned int GetShaderUniformLocation(unsigned int shaderProgramID, const char* name);
//
//    static void   EnableShaderProgram(unsigned int shaderProgramID);
//    static void   DisableShaderProgram();
};
#endif
