#ifndef _grafx_angle
#define _grafx_angle

#include <math.h>

#define GFX_PI 3.14159

typedef enum {
    GFX_ANGLE_FORMAT_RADIAN,
    GFX_ANGLE_FORMAT_DEGREE
} GFX_ANGLE_FORMAT;

typedef struct {
    GFX_ANGLE_FORMAT format; 
    double value;
} GFX_Angle;

GFX_Angle GFX_AngleFromDeg(double value);
GFX_Angle GFX_AngleFromRad(double value);

GFX_Angle GFX_AngleDegToRad(GFX_Angle angle);
GFX_Angle GFX_AngleRadToDeg(GFX_Angle angle);

#endif