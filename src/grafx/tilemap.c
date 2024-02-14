#include "tilemap.h"

static GFX_TileMap *TileMapCreate(void)
{
    return (GFX_TileMap *)calloc(1, sizeof(GFX_TileMap));
}

GFX_TileMap *GFX_TileMapConstruct(Uint16 width, Uint16 height)
{
    Uint16 rows_created, cols_created;  // loop counters

    check(width != 0, "Width must be non-zero.");
    check(height != 0, "Height must be non-zero.");

    GFX_TileMap *tilemap = TileMapCreate();
    check_mem(tilemap);

    tilemap->width = width;
    tilemap->height = height;

    tilemap->tiles = (GFX_Tile ***)calloc(width, sizeof(GFX_Tile **));
    check_mem(tilemap->tiles);

    for(cols_created = 0; cols_created < width; cols_created++){
        tilemap->tiles[cols_created] = (GFX_Tile **)calloc(height, sizeof(GFX_Tile *));
        check_mem(tilemap->tiles[cols_created]);
        for(rows_created = 0; rows_created < height; rows_created++){
            tilemap->tiles[rows_created] = GFX_TileConstruct(NULL, NULL,    //Create placeholder tiles
                                                                (double)cols_created,
                                                                (double)rows_created,
                                                                0);
        }
    }

    return tilemap;
error:
    for(Uint16 x = 0; x < cols_created; x++){
        for(Uint16 y = 0; y < rows_created; y++){
            GFX_TileDestroy(tilemap->tiles[x][y]);
        }
        free(tilemap->tiles[x]);
    }

    if(tilemap->tiles) free(tilemap->tiles);
    free(tilemap);

    return NULL;
}

void GFX_TileMapDestroy(GFX_TileMap *tilemap)
{
    for(Uint16 x = 0; x < tilemap->width; x++){
        for(Uint16 y = 0; y < tilemap->height; y++){
            GFX_TileDestroy(tilemap->tiles[x][y]);
        }
        free(tilemap->tiles[x]);
    }
    free(tilemap->tiles);
    free(tilemap);
}