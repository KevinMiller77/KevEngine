#include "ShaderArray.h"

void ShaderArray::addShader(const char* ID, ShaderProgram* shader)
{
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}

void ShaderArray::newShader(const char* ID, const char* vertex_file_path, const char* fragment_file_path)
{
    ShaderProgram* shader = new ShaderProgram(vertex_file_path, fragment_file_path);
    shaders.push_back(shader);
    shaderMap[ID] = shaders.size() - 1;
}