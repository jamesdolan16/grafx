#include "angle.h"

#include <math.h>


GFX_Angle GFX_AngleFromDeg(double value)
{
    return (GFX_Angle){.value = value, .format=GFX_ANGLE_FORMAT_DEGREE};
}

GFX_Angle GFX_AngleFromRad(double value)
{
    return (GFX_Angle){.value = value, .format=GFX_ANGLE_FORMAT_RADIAN};
}

GFX_Angle GFX_AngleDegToRad(GFX_Angle angle)
{
    return (GFX_Angle){.value = (angle.value * (GFX_PI / 180.0)), .format=GFX_ANGLE_FORMAT_RADIAN};
}

GFX_Angle GFX_AngleRadToDeg(GFX_Angle angle)
{
    return (GFX_Angle){.value = (angle.value * (180.0 / GFX_PI)), .format=GFX_ANGLE_FORMAT_DEGREE};
}