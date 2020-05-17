//
//  Simple.metal
//  MetalShaders
//
//  Created by Kevin Miller on 5/16/20.
//
#include <metal_stdlib>
using namespace metal;

struct VertexIn
{
    float3 pos;
    float2 texture;
    float texID;
    unsigned int color;
};

struct VertexOut
{
    float4 pos [[position]];
    float2 texture;
    float texID;
    unsigned int color;
};

vertex VertexOut simple_vertex(device VertexIn* in [[buffer(0)]],
                               uint vid [[vertex_id]])
{
    VertexOut out;
    out.pos = vector_float4(in[vid].pos.xyz, 0.0f);
    out.texture = in[vid].texture;
    out.texID = in[vid].texID;
    out.color = in[vid].color;
    return out;
}

fragment half4 simple_fragment(VertexOut in [[stage_in]])
{
    return half4(1);
    //return in.color;
}
