#ifndef __SHADER_ARRAY__
#define __SHADER_ARRAY__

#include "ShaderProgram.h"

class ShaderArray
{
private:
    std::map<const char*, GLuint, StrCompare> shaderMap;
    std::vector<ShaderProgram*> shaders;

public:
    ShaderArray() = default;
    ~ShaderArray()
    {
        shaders.clear();
    }

    void addShader(const char* ID, ShaderProgram* shader);
    void newShader(const char* ID, const char* vertex_file_path, const char* fragment_file_path);
    inline ShaderProgram getShader(const char* ID) { return *(shaders[shaderMap[ID]]);}
    inline ShaderProgram* getShaderPtr(const char* ID) { return shaders[shaderMap[ID]]; }

    inline void enable(const char* ID) { shaders[shaderMap[ID]]->enable(); }
    inline void disable(const char* ID) { shaders[shaderMap[ID]]->disable(); }

    inline void clearShaders() { shaders.clear(); shaderMap.clear(); }

    inline void setUniform1f(const char * ID, const GLchar* name, float value)                      { shaders[shaderMap[ID]]->setUniform1f(name, value); }
    inline void setUniform1fv(const char * ID, const GLchar* name, float* value, GLsizei count)     { shaders[shaderMap[ID]]->setUniform1fv(name, value, count); }
    inline void setUniform1i(const char * ID, const GLchar* name, int value)                        { shaders[shaderMap[ID]]->setUniform1i(name, value); }
    inline void setUniform1iv(const char * ID, const GLchar* name, int* value, GLsizei count)       { shaders[shaderMap[ID]]->setUniform1iv(name, value, count); }
    inline void setUniform2f(const char * ID, const GLchar* name, const Vec2f& vector)              { shaders[shaderMap[ID]]->setUniform2f(name, vector); }
    inline void setUniform3f(const char * ID, const GLchar* name, const Vec3f& vector)              { shaders[shaderMap[ID]]->setUniform3f(name, vector); }
    inline void setUniform4f(const char * ID, const GLchar* name, const Vec4f& vector)              { shaders[shaderMap[ID]]->setUniform4f(name, vector); }
    inline void setUniformMat4(const char * ID, const GLchar* name, const Mat4f& matrix)            { shaders[shaderMap[ID]]->setUniformMat4(name, matrix); }

    inline GLuint getUniformLocation(const char* ID, const GLchar* name) { return shaders[shaderMap[ID]]->getUniformLocation(name); }

    void _delete() {
        for (ShaderProgram* shader : shaders)
            delete shader;
        shaderMap = std::map<const char*, GLuint, StrCompare>();
    }

};

#endif
