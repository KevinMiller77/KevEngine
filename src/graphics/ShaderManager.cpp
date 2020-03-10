#include "ShaderManager.h"

void ShaderManager::addShader(const char* ID, ShaderProgram* shader)
{
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}

void ShaderManager::newShader(const char* ID, const char* vertex_file_path, const char* fragment_file_path)
{
    ShaderProgram* shader = new ShaderProgram(vertex_file_path, fragment_file_path);
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}

void ShaderManager::clearShaders() 
{ 
    for (ShaderProgram* shader : shaders)
    {
        delete shader;
    }

    shaders.clear(); 
    shaderMap.clear(); 
}