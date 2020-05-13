#ifndef __KEV_TILEMAP_TILE__
#define __KEV_TILEMAP_TILE__

#include <graphics/layers/Group.h>
#include <graphics/renderables/Sprite.h>

class TileMapTile : public Group
{
    Vec2u mapPos = Vec2u(0, 0);
    Vec2u textureIndex = Vec2u(0, 0);
    
public:
    TileMapTile(Vec2u& MapPos, TextureProgram* TileMap, Vec2u& TextureIndex);
    
    inline void Rotate(float angle) { AddTransform(Mat4f::rotation(angle, Vec3f(0, 0, 1))); }
  
    inline const Vec2u GetMapPos() { return mapPos; }
    
    inline const Vec2u GetAtlas() { return textureIndex; }
    inline const void SetAtlas(Vec2u NewAtlas) { textureIndex = NewAtlas; }
    
};

#endif
