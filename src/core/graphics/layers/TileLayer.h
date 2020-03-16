#ifndef __KevEngine_TILE_LAYER__
#define __KevEngine_TILE_LAYER__

#include "Layer.h"
#include "../BetterGL2DRenderer.h"

class TileLayer : public Layer
{
public:
    TileLayer(GLuint shader);

    void OnAttach() override {};
    void OnDetatch() override {};
    void OnUpdate() override {};
    void OnDraw() override {};
    void OnEvent(Event& e) override {};

};

#endif