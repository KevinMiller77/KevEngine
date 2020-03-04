#ifndef __TLETC_TILE_LAYER__
#define __TLETC_TILE_LAYER__

#include "Layer.h"

class TileLayer : public Layer
{
public:
    TileLayer(ShaderProgram *shader);
    ~TileLayer();
};

#endif