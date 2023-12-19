#ifndef _grafx_entity_h
#define _grafx_entity_h

// Store information about any "thing" that can exist in the game world
typedef struct {
    Uint32 id;
    float x;
    float y;
    GFX_Angle angle;
} GFX_Entity;

#endif