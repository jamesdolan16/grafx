#include "tile.h"

static GFX_Tile *TileCreate(void)
{
    return (GFX_Tile *)calloc(1, sizeof(GFX_Tile));
}

GFX_Tile *GFX_TileConstruct(const_bstring id, GFX_TileType *tiletype, float x, float y, float h)
{
    check(tiletype != NULL, "Null tiletype provided.");

    GFX_Tile *tile = TileCreate();
    check_mem(tile);

    *tile = (GFX_Tile){.base = {.id = id, .x = x, .y = y, .h = h, .angle = 0}, .tiletype = tiletype };

    return tile;
error:
    return NULL;
}

void GFX_TileDestroy(GFX_Tile *tile)
{
    check(tile != NULL, "Null tile provided.");
    
    free(tile);
error:
}