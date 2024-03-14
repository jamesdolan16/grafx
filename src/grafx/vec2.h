#ifndef _grafx_vec2_h
#define _grafx_vec2_h

#include "angle.h"

typedef struct GFX_Angle GFX_Angle;

typedef struct GFX_Vec2{
    double x, y;
} GFX_Vec2;

GFX_Vec2 GFX_Vec2FromAngle(GFX_Angle angle);

#endif