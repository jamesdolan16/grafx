#ifndef _grafx_sprite_h
#define _grafx_sprite_h

#include <stdlib.h>

#include "dbg.h"
#include "angle.h"
#include "texture.h"

typedef struct {
    GFX_Entity base;
    GFX_Texture *texture;
} GFX_Sprite;

GFX_Sprite *GFX_SpriteCreate();
GFX_Sprite *GFX_SpriteConstruct(float x, float y, GFX_Angle angle, GFX_Texture *texture);
void GFX_SpriteDestroy(GFX_Sprite *sprite);

#endif