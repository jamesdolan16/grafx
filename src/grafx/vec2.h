#ifndef _grafx_vec2_h
#define _grafx_vec2_h

#include "grafx.h"

typedef struct{
    double x, y;
} GFX_Vec2;

GFX_Vec2 GFX_Vec2FromAngle(GFX_Angle angle)
{
    GFX_Angle rad;

    if(angle.format == GFX_ANGLE_FORMAT_DEGREE){
        rad = GFX_AngleDegToRad(angle);
    } else {
        rad = angle;
    }

    return (GFX_Vec2){ .x = cosf(rad.value), .y = sinf(rad.value) };
}

#endif