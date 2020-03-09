#include "TileLayer.h"

TileLayer::TileLayer(GLuint shader)
    : Layer(new Renderer2D(), shader, Mat4f::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}