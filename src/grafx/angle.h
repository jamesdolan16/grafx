#ifndef _grafx_angle_h
#define _grafx_angle_h

#include <math.h>

#include "dbg.h"
#include "vec2.h"

#define GFX_PI 3.14159
#define GFX_ANGLE_MIN_ACCURACY 0.000001
#define GFX_ANGLE_EQ(a, b) fabs(a - b) <= GFX_ANGLE_MIN_ACCURACY

typedef struct GFX_Vec2 GFX_Vec2;

typedef enum {
    GFX_ANGLE_FORMAT_RADIAN,
    GFX_ANGLE_FORMAT_DEGREE
} GFX_ANGLE_FORMAT;

/**
 * Container for angle values
*/
typedef struct GFX_Angle{
    GFX_ANGLE_FORMAT format; 
    double value;
} GFX_Angle;

/**
 * Create an Angle from a degree value
*/
GFX_Angle GFX_AngleFromDeg(double value);

/**
 * Create an Angle from a radian value
*/
GFX_Angle GFX_AngleFromRad(double value);

/**
 * Convert an Angle with Angle Format degrees to radians
*/
GFX_Angle GFX_AngleDegToRad(GFX_Angle angle);

/**
 * Convert an Angle with Angle Format radians to degrees
*/
GFX_Angle GFX_AngleRadToDeg(GFX_Angle angle);

/**
 * Convert a Vec2 to an Angle with the angle format specified
*/
GFX_Angle GFX_AngleFromVec2(GFX_Vec2 vec2, GFX_ANGLE_FORMAT format);

/**
 * Create an Angle that is at a right angle to the provided Angle
*/
GFX_Angle GFX_AngleRightAngle(GFX_Angle angle);

#endif