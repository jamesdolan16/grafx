#include "tiletype.h"

static GFX_TileType *TileTypeCreate(void)
{
    return (GFX_TileType *)calloc(1, sizeof(GFX_TileType));
}

GFX_TileType *GFX_TileTypeConstruct(const_bstring id, SDL_Surface *surface, SDL_bool is_solid)
{
    check(surface != NULL, "Null texture provided.");

    GFX_TileType *tiletype = TileTypeCreate();
    check_mem(tiletype);

    *tiletype = (GFX_TileType){.id = id, .surface = surface, .is_solid = is_solid};

    return tiletype;
error:
    return NULL;
}

void GFX_TileTypeDestroy(GFX_TileType *tiletype)
{
    check(tiletype != NULL, "Null tiletype provided.");

    free(tiletype);
error:
}