#ifndef __KEV_TILEMAP_GROUP__
#define __KEV_TILEMAP_GROUP__

#include <graphics/layers/Group.h>
#include <graphics/renderables/TileMapTile.h>

class TileMap : public Group
{
    Vec2u sceneSize;
    std::map<int, TileMapTile*> tiles;
    Texture* tilesheet;
    
public:
    TileMap(Vec2f GamespaceExtremes, Texture* Tilesheet);
    
    void NewTile(Vec2u Pos, Vec2u Atlas);
    inline TileMapTile* GetTile(Vec2u Pos) { return tiles[Pos.x * sceneSize.y + Pos.y]; }
    
};

#endif
