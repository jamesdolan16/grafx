#include "tilemap.h"

static GFX_TileMap *TileMapCreate(void)
{
    return (GFX_TileMap *)calloc(1, sizeof(GFX_TileMap));
}

static SDL_Surface *load_texture(const char *path)
{
    SDL_Surface *src_texture = IMG_Load(path);
    check_sdl_ptr(src_texture);

    SDL_Surface *dst_texture = SDL_ConvertSurfaceFormat(src_texture, SDL_PIXELFORMAT_ARGB8888, 0);
    check_sdl_ptr(dst_texture);

    SDL_FreeSurface(src_texture);

    return dst_texture;
error:
    return NULL;
}

GFX_TileMap *GFX_TileMapConstruct(Uint16 width, Uint16 height)
{
    Uint16 rows_created = 0, cols_created = 0;  // loop counters

    GFX_TileMap *tilemap = TileMapCreate();
    check_mem(tilemap);
    
    check(width != 0, "Width must be non-zero.");
    check(height != 0, "Height must be non-zero.");

    tilemap->width = width;
    tilemap->height = height;

    tilemap->tiles = (GFX_Tile ***)calloc(width, sizeof(GFX_Tile **));
    check_mem(tilemap->tiles);

    for(cols_created = 0; cols_created < width; cols_created++){
        tilemap->tiles[cols_created] = (GFX_Tile **)calloc(height, sizeof(GFX_Tile *));
        check_mem(tilemap->tiles[cols_created]);
        for(rows_created = 0; rows_created < height; rows_created++){
            tilemap->tiles[cols_created][rows_created] = GFX_TileConstruct(NULL, NULL,    //Create placeholder tiles
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

GFX_TileMap *GFX_TileMapFromIntArray(int *map_array, const Uint16 width, const Uint16 height)
{
    Uint16 tilecount = 8;
    GFX_TileType **tiletypes = calloc(tilecount, sizeof(GFX_TileType));

    int i = 0;
    //tiletypes[i++] = GFX_TileTypeConstruct(NULL, NULL, SDL_FALSE);  // Free space
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/redbrick.png"), SDL_FALSE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/redbrick.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/bluestone.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/colorstone.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/eagle.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/wood.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/greystone.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/mossy.png"), SDL_TRUE);
    tiletypes[i++] = GFX_TileTypeConstruct(NULL, load_texture("resources/images/purplestone.png"), SDL_TRUE);

    GFX_TileMap *tilemap = GFX_TileMapConstruct(width, height);
    check_mem(tilemap);

    for(Uint16 x = 0; x < width; x++){
        for(Uint16 y = 0; y < height; y++){
            tilemap->tiles[x][y]->tiletype = tiletypes[map_array[y * width + x]];
        }
    }

    return tilemap;
error:
    if(tiletypes){
        for(Uint16 i = 0; i < tilecount; i++){
            GFX_TileTypeDestroy(tiletypes[i]);
        }

        free(tiletypes);
    }
    
    GFX_TileMapDestroy(tilemap);

    return NULL;
}