#include "ShaderProgram.h"

#include <core/Core.h>
#include <platform/graphics/Metal/renderer/MetalShaderProgram.h>
#include <platform/graphics/GL/renderer/GLShaderProgram.h>


ShaderProgram* ShaderProgram::Create(const char* VertexIn, const char* FragmentIn)
{
#ifdef KEV_RENDERAPI_GL
    return new GLShaderProgram(VertexIn, FragmentIn);
#elif defined KEV_RENDERAPI_METAL
    return new MetalShaderProgram(VertexIn, FragmentIn);
#endif
}

void EnableShaderProgram(ShaderProgram* Shader)
{
#ifdef KEV_RENDERAPI_GL
    ((GLShaderProgram*)Shader)->Enable();
#elif defined KEV_RENDERAPI_METAL
    ((MetalShaderProgram*)Shader)->Enable();
#endif
}
