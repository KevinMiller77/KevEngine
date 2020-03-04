#ifndef __TLETC_TILE_LAYER__
#define __TLETC_TILE_LAYER__

#include "Layer.h"
#include "../BetterGL2DRenderer.h"

class TileLayer : public Layer
{
public:
    TileLayer(ShaderProgram *shader);
};

#endif