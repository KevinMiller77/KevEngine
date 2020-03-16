#include "TileLayer.h"

TileLayer::TileLayer(GLuint shader)
    : Layer(new BetterGL2DRenderer(), shader)
{
}