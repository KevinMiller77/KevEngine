#include "TileMapTile.h"

TileMapTile::TileMapTile(Vec2u& MapPos, TextureProgram* TileMap, Vec2u& TextureIndex) : Group(Mat4f::translation(Vec3f((float) MapPos.x, (float) MapPos.y, 0)))
{
    mapPos = MapPos;
    textureIndex = TextureIndex;
    Add(new Sprite(0, 0, 1, 1, TileMap, TextureIndex));
    type = RenderableType::Tile;
}
