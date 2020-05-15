#include <metal_stdlib>
#include <simd/simd.h>
using namespace metal;

typedef struct
{
    vector_float3 vert;
    vector_float2 texture;
    float texID;
    unsigned int color;
}  VertexIn;

typedef struct
{
    vector_float4 vert [[position]];
    vector_float2 texture;
    float texID;
    unsigned int color;
} VertexOut;

vertex VertexOut vertexFunction(device VertexIn* verticies [[buffer(0)]], uint vid [[vertex_id]])
{
    VertexOut out;
    out.position = vector_float4(verticies[vid].vert.xyz, 0.0f);
    out.texture = verticies.texture;
    out.texID = verticies.texID;
    out.color = verticies.color;
    return out;
}

fragment float4 fragmentFunction(VertexOut in [[stage_in]])
{
    return in.color;
}
