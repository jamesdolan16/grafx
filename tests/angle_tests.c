#include "minunit.h"

#include <grafx/angle.h>

char *test_AngleDegToRad()
{
    GFX_Angle a, b;

    a = GFX_AngleFromDeg(180.0);
    b = GFX_AngleDegToRad(a);

    mu_assert(fabs(b.value - GFX_PI) < GFX_ANGLE_MIN_ACCURACY, "Failed to convert degress to radians accurately");

    return NULL;
}

char *test_AngleRadToDeg()
{
    GFX_Angle a, b;

    a = GFX_AngleFromRad(GFX_PI);   // Equivalent to 180deg
    b = GFX_AngleRadToDeg(a);

    mu_assert(fabs(b.value - 180) < GFX_ANGLE_MIN_ACCURACY, "Failed to convert radians to degrees accurately");

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