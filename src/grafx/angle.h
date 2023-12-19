#ifndef _grafx_angle
#define _grafx_angle

typedef enum {
    GFX_ANGLE_FORMAT_RADIAN,
    GFX_ANGLE_FORMAT_DEGREE
} GFX_ANGLE_FORMAT;

typedef struct {
    GFX_ANGLE_FORMAT format; 
    double val;
} GFX_Angle;

#endif