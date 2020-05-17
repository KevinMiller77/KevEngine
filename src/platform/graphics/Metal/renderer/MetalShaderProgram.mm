#include <platform/graphics/Metal/renderer/MetalShaderProgram.h>
//#include <../resources/shaders/MSL/Simple.metal>

MetalShaderProgram::MetalShaderProgram(const char* vertex_file_name, const char* fragment_file_name)
{
    NSString* vert = [NSString stringWithUTF8String:vertex_file_name];
    NSString* frag = [NSString stringWithUTF8String:fragment_file_name];
    
    id<MTLLibrary> defLib = [GET_METAL_DEVICE() newLibraryWithFile:@"resources/shaders/MSL/KevShaderLib.metallib" error:nil];
    id<MTLFunction> vertexShader = [defLib newFunctionWithName:vert];
    id<MTLFunction> fragmentShader = [defLib newFunctionWithName:frag];
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    [pipelineStateDescriptor setLabel:@"KevEngine"];
    [pipelineStateDescriptor setVertexFunction:vertexShader];
    [pipelineStateDescriptor setFragmentFunction:fragmentShader];
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;

    m_Shader = [GET_METAL_DEVICE() newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:nil];

}
//
//unsigned int MetalShaderProgram::CreateMetalProgram(const char* vertex_file_path, const char* fragment_file_path) 
//{
//    return 0;
//}
//
//unsigned int MetalShaderProgram::RefreshMetalProgram(const char* vertex_file_path, const char* fragment_file_path) 
//{
//    return 0;
//}
//
//
//
//void   MetalShaderProgram::SetUniform1f(const char* ID, float value)
//{
//}
//
//void  MetalShaderProgram::SetUniform1fv(const char* ID, float* value, int count)
//{
//}
//
//void   MetalShaderProgram::SetUniform1i(const char* ID, int value)
//{
//}
//
//
//void   MetalShaderProgram::SetUniform1iv(const char* ID, int* value, int count)
//{
//}
//void   MetalShaderProgram::SetUniform2f(const char* ID, const Vec2f& vector)
//{
//}
//
//void   MetalShaderProgram::SetUniform3f(const char* ID, const Vec3f& vector)
//{
//}
//
//void   MetalShaderProgram::SetUniform4f(const char* ID, const Vec4f& vector)
//{
//}
//
//void   MetalShaderProgram::SetUniformMat4(const char* ID, const Mat4f& matrix)
//{
//}
//
//unsigned int MetalShaderProgram::GetUniformLocation(const char* ID)
//{
//}
//
//void   MetalShaderProgram::Enable()
//{
//}
//
//void   MetalShaderProgram::Disable()
//{
//}
//
//void MetalShaderProgram::EnableShaderProgram(unsigned int shaderProgramID)
//{
//}
//
//void MetalShaderProgram::DisableShaderProgram()
//{
//}
