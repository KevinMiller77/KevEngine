#ifndef __TLETC_TILE_LAYER__
#define __TLETC_TILE_LAYER__

#include "Layer.h"
#include "../Renderer2D.h"

class TileLayer : public Layer
{
public:
    TileLayer(GLuint shader);
};

#endif