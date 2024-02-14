#ifndef _grafx_entity_h
#define _grafx_entity_h

#include "grafx.h"

/**
 * Store information about any "thing" that can exist in the game world
*/
typedef struct {
    const_bstring id;          // Unique identifier for this object
    float x;            // X position in the level
    float y;            // Y position in the level
    float h;            // Vertical height
    GFX_Angle angle;    // Direction this object is facing
} GFX_Entity;

#endif