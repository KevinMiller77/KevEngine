#include "TileLayer.h"

TileLayer::TileLayer(GLuint shader)
    : Layer(new BetterGL2DRenderer(), shader, Mat4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f))
{
}