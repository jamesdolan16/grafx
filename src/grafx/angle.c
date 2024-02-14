#include "angle.h"

GFX_Angle GFX_AngleFromDeg(double value)
{
    return (GFX_Angle){.value = value, .format = GFX_ANGLE_FORMAT_DEGREE};
}

GFX_Angle GFX_AngleFromRad(double value)
{
    return (GFX_Angle){.value = value, .format = GFX_ANGLE_FORMAT_RADIAN};
}

GFX_Angle GFX_AngleDegToRad(GFX_Angle angle)
{
    return (GFX_Angle){.value = (angle.value * (GFX_PI / 180.0)), .format = GFX_ANGLE_FORMAT_RADIAN};
}

GFX_Angle GFX_AngleRadToDeg(GFX_Angle angle)
{
    return (GFX_Angle){.value = (angle.value * (180.0 / GFX_PI)), .format = GFX_ANGLE_FORMAT_DEGREE};
}

GFX_Angle GFX_AngleFromVec2(GFX_Vec2 vec2, GFX_ANGLE_FORMAT format)
{
    check(vec2.x != 0 && vec2.y != 0, "Provided a zero-vector");

    GFX_Angle angle = {.value = atan2f(vec2.y, vec2.x), .format = GFX_ANGLE_FORMAT_RADIAN};

    if(format == GFX_ANGLE_FORMAT_DEGREE) angle = GFX_AngleRadToDeg(angle);
    
    return angle;
error:
    return (GFX_Angle){ .value = 0, .format = GFX_ANGLE_FORMAT_RADIAN };    // Return default angle
}

GFX_Angle GFX_AngleRightAngle(GFX_Angle angle)
{
    double additive = 0;

    switch(angle.format){
    case GFX_ANGLE_FORMAT_DEGREE:
        additive = 90;
        break;
    default:                                // Fall through to radian label after logging the error
        log_err("Invalid angle.format provided, defaulting to radians");
    case GFX_ANGLE_FORMAT_RADIAN:
        additive = GFX_PI/2;
        break;
    }

    return (GFX_Angle){ .value = angle.value + additive, .format = angle.format };
}