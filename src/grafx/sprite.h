#ifndef _grafx_sprite_h
#define _grafx_sprite_h

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "grafx.h"

typedef struct GFX_Sprite{
    GFX_Entity base;
    GFX_Texture *texture;
} GFX_Sprite;

/**
 * Creates a Sprite with the provided attributes
 * 
 * @param x X-coordinate of the sprite
 * @param y Y-coordinate of the sprite
 * @param angle Sprites direction given as an angle from north
 * 
 * @returns Pointer to the newly created Sprite or NULL upon failure
*/
GFX_Sprite *GFX_SpriteConstruct(float x, float y, GFX_Angle angle, GFX_Texture *texture);
void GFX_SpriteDestroy(GFX_Sprite *sprite);


#endif