#ifndef _grafx_stage_h
#define _grafx_stage_h

#include <lcthw/darray.h>

#include "tilemap.h"
#include "buffer.h"
#include "bstrlib.h"
#include "sprite.h"

/**
 * Stores all the data associated with a stage (tilemap and sprites)
*/
typedef struct{
    const_bstring id;
    GFX_TileMap *tilemap;
    DArray *sprites;
} GFX_Stage;

GFX_Stage *GFX_StageContruct(const_bstring id, GFX_TileMap *tilemap);
void GFX_StageDestroy(GFX_Stage *stage);

#endif
