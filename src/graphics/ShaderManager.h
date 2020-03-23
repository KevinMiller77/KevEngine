#ifndef __SHADER_MANAGER__
#define __SHADER_MANAGER__

#include <graphics/renderer/ShaderProgram.h>

class ShaderManager
{
private:
    std::map<const char*, unsigned int, StrCompare> shaderMap;
    std::vector<ShaderProgram*> shaders;

public:
    ShaderManager() = default;
    ~ShaderManager()
    {
        for (ShaderProgram* shader : shaders)
        {
            delete shader;
        }
        shaders.clear();
        shaderMap.clear();
    }

    void AddShader(const char* ID, ShaderProgram* shader);
    void ClearShaders();
    void NewShader(const char* ID, const char* vertex_file_path, const char* fragment_file_path);
    inline ShaderProgram GetShader(const char* ID) { return *(shaders[shaderMap[ID]]);}
    inline ShaderProgram* GetShaderPtr(const char* ID) { return shaders[shaderMap[ID]]; }

    inline void Enable(const char* ID) { if (!shaders.empty()) shaders[shaderMap[ID]]->Enable(); }
    inline void Disable(const char* ID) { if (!shaders.empty()) shaders[shaderMap[ID]]->Disable(); }


    inline void SetUniform1f(const char * ID, const char* name, float value)                      { shaders[shaderMap[ID]]->SetUniform1f(name, value); }
    inline void SetUniform1fv(const char * ID, const char* name, float* value, int count)     { shaders[shaderMap[ID]]->SetUniform1fv(name, value, count); }
    inline void SetUniform1i(const char * ID, const char* name, int value)                        { shaders[shaderMap[ID]]->SetUniform1i(name, value); }
    inline void SetUniform1iv(const char * ID, const char* name, int* value, int count)       { shaders[shaderMap[ID]]->SetUniform1iv(name, value, count); }
    inline void SetUniform2f(const char * ID, const char* name, const Vec2f& vector)              { shaders[shaderMap[ID]]->SetUniform2f(name, vector); }
    inline void SetUniform3f(const char * ID, const char* name, const Vec3f& vector)              { shaders[shaderMap[ID]]->SetUniform3f(name, vector); }
    inline void SetUniform4f(const char * ID, const char* name, const Vec4f& vector)              { shaders[shaderMap[ID]]->SetUniform4f(name, vector); }
    inline void SetUniformMat4(const char * ID, const char* name, const Mat4f& matrix)            { shaders[shaderMap[ID]]->SetUniformMat4(name, matrix); }

    inline unsigned int GetUniformLocation(const char* ID, const char* name) { return shaders[shaderMap[ID]]->GetUniformLocation(name); }

    void _delete() {
        for (ShaderProgram* shader : shaders)
            delete shader;
        shaderMap = std::map<const char*, unsigned int, StrCompare>();
    }

};

#endif
