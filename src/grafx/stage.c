#include "stage.h"

static GFX_Stage *StageCreate()
{
    return (GFX_Stage *)calloc(1, sizeof(GFX_Stage));
}

GFX_Stage *GFX_StageContruct(const_bstring id, GFX_Buffer *buffer, GFX_TileMap *tilemap)
{
    check(buffer != NULL, "Null buffer provided.");
    check(tilemap != NULL, "Null tilemap provided.");

    GFX_Stage *stage = StageCreate();
    check_mem(stage);

    stage->tilemap = tilemap;

    return stage;
error:
    return NULL;
}

void GFX_StageDestroy(GFX_Stage *stage)
{
    check(stage != NULL, "Null stage provided.");
    
    free(stage);
error:
}

