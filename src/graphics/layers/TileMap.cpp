#include "TileMap.h"

TileMap::TileMap(Vec2f GamespaceExtremes, Texture* Tilesheet) : Group(Mat4f::translation(Vec3f(-GamespaceExtremes.x, -GamespaceExtremes.y, 0)))
{
    sceneSize = Vec2u((int)GamespaceExtremes.x * 2, (int)GamespaceExtremes.y * 2);
    tilesheet = Tilesheet;
}

void TileMap::NewTile(Vec2u Pos, Vec2u Atlas)
{
    TileMapTile* newTile = new TileMapTile(Pos, tilesheet, Atlas);
    int pos = Pos.x * sceneSize.y + Pos.y;
    tiles[pos] = newTile;
    Add(newTile);
}
