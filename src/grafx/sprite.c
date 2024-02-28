#include "sprite.h"

/**
 * Allocated a Sprite on the heap
*/
static GFX_Sprite *SpriteCreate()
{
    GFX_Sprite *sprite = (GFX_Sprite *)calloc(1, sizeof(GFX_Sprite));

    return sprite;
}


GFX_Sprite *SpriteConstruct(float x, float y, GFX_Angle angle, SDL_Surface *texture)
{
    GFX_Sprite *sprite = SpriteCreate();
    check_mem(sprite);

    *sprite = (GFX_Sprite){ .base={.x=x, .y=y, .angle=angle}, .texture = texture,
                            .h_scale=1, .v_scale=1, .v_pos=0.0 };

    return sprite;
error:
    return NULL;
}

void GFX_SpriteDestroy(GFX_Sprite *sprite)
{
    check(sprite != NULL, "Null sprite provided.");

    GFX_TextureDestroy(sprite->texture);
error:
}