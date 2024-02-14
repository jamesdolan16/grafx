#include "minunit.h"

#include <grafx/angle.h>

char *test_AngleDegToRad()
{
    GFX_Angle a, b;

    a = GFX_AngleFromDeg(180.0);
    b = GFX_AngleDegToRad(a);

    mu_assert(GFX_ANGLE_EQ(b.value, GFX_PI), "Failed to convert degress to radians accurately");

    return NULL;
}

char *test_AngleRadToDeg()
{
    GFX_Angle a, b;

    a = GFX_AngleFromRad(GFX_PI);   // Equivalent to 180deg
    b = GFX_AngleRadToDeg(a);

    mu_assert(GFX_ANGLE_EQ(b.value, 180), "Failed to convert radians to degrees accurately");

    return NULL;
}

char *test_AngleFromVec2()
{
    GFX_Angle angle;
    GFX_Vec2 vec2;

    vec2 = (GFX_Vec2){ .x = 1.0, .y = 0 };
    angle = GFX_AngleFromVec2(vec2, GFX_ANGLE_FORMAT_RADIAN);
    mu_assert(GFX_ANGLE_EQ(angle.value, 0), "Failed Input Boundary Test");

    vec2 = (GFX_Vec2){ .x = sqrt(2)/2, .y = sqrt(2)/2 };
    angle = GFX_AngleFromVec2(vec2, GFX_ANGLE_FORMAT_RADIAN);
    mu_assert(GFX_ANGLE_EQ(angle.value, GFX_PI/4), "Failed Positive Angle Test");

    vec2 = (GFX_Vec2){ .x = 0.5, .y = -sqrt(3)/2 };
    angle = GFX_AngleFromVec2(vec2, GFX_ANGLE_FORMAT_RADIAN);
    mu_assert(GFX_ANGLE_EQ(angle.value, -GFX_PI/3), "Failed Negative Angle Test");

    vec2 = (GFX_Vec2){ .x = -0.5, .y = -sqrt(3)/2 };
    angle = GFX_AngleFromVec2(vec2, GFX_ANGLE_FORMAT_RADIAN);
    mu_assert(GFX_ANGLE_EQ(angle.value, 5*GFX_PI/3), "Failed Large Angle Test");

    vec2 = (GFX_Vec2){ .x = 0.0, .y = 0.0 };
    angle = GFX_AngleFromVec2(vec2, GFX_ANGLE_FORMAT_RADIAN);
    mu_assert(GFX_ANGLE_EQ(angle.value, 0.0), "Failed Zero-Angle Test");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_AngleDegToRad);
    mu_run_test(test_AngleRadToDeg);

    return NULL;
}

RUN_TESTS(all_tests);