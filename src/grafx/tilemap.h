#ifndef _grafx_tilemap_h
#define _grafx_tilemap_h

#include "tile.h"

typedef struct {
    GFX_Tile ***tiles;      // I know it's horrible, boohoo! I need a 2D array of tile pointers!
    Uint16 width;
    Uint16 height;
} GFX_TileMap;

GFX_TileMap *GFX_TileMapConstruct(Uint16 width, Uint16 height);

/**
 * Destroys the tilemap and all the tiles contained within
*/
void GFX_TileMapDestroy(GFX_TileMap *tilemap);

#endif