#include "ShaderManager.h"

void ShaderManager::AddShader(const char* ID, GLShaderProgram* shader)
{
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}

void ShaderManager::NewShader(const char* ID, const char* vertex_file_path, const char* fragment_file_path)
{
    GLShaderProgram* shader = new GLShaderProgram(vertex_file_path, fragment_file_path);
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}

void ShaderManager::ClearShaders() 
{ 
    for (GLShaderProgram* shader : shaders)
    {
        delete shader;
    }

    shaders.clear(); 
    shaderMap.clear(); 
}
