#include "sprite.h"

/**
 * Creates an empty Sprite struct
 * 
 * @returns Pointer to the newly created Sprite or NULL upon failure
 */
GFX_Sprite *GFX_SpriteCreate()
{
    GFX_Sprite *sprite = (GFX_Sprite *)calloc(1, sizeof(GFX_Sprite));

    return sprite;
}

/**
 * Creates a Sprite with the provided attributes
 * 
 * @param x X-coordinate of the sprite
 * @param y Y-coordinate of the sprite
 * @param angle Sprites direction given as an angle from north
 * 
 * @returns Pointer to the newly created Sprite or NULL upon failure
*/
GFX_Sprite *SpriteConstruct(float x, float y, GFX_Angle angle, GFX_Texture *texture)
{
    GFX_Sprite *sprite = GFX_SpriteCreate();
    check_mem(sprite);

    *sprite = (GFX_Sprite){ .base={.x=x, .y=y, .angle=angle}, .texture = texture };

    return sprite;
error:
    return NULL;
}