#ifndef _grafx_tile_h
#define _grafx_tile_h

#include "entity.h"
#include "tiletype.h"
#include "tile.h"
#include "bstrlib.h"

#define GFX_TILE_WIDTH 64

typedef struct {
    GFX_Entity base;
    GFX_TileType *tiletype;
} GFX_Tile;

GFX_Tile *GFX_TileConstruct(const_bstring id, GFX_TileType *tiletype, double x, double y, double h);

void GFX_TileDestroy(GFX_Tile *tile);


#endif