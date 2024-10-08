#include "stage.h"

static GFX_Stage *StageCreate()
{
    return (GFX_Stage *)calloc(1, sizeof(GFX_Stage));
}

GFX_Stage *GFX_StageContruct(const_bstring id, GFX_TileMap *tilemap)
{
    GFX_Stage *stage = StageCreate();
    check_mem(stage);
    
    check(tilemap != NULL, "Null tilemap provided.");

    stage->sprites = DArray_create(sizeof(GFX_Sprite), 32);
    check_mem(stage->sprites);

    stage->tilemap = tilemap;

    return stage;
error:
    if(stage) GFX_StageDestroy(stage);
    return NULL;
}

void GFX_StageDestroy(GFX_Stage *stage)
{
    check(stage != NULL, "Null stage provided.");
    
    free(stage);
error:
}

