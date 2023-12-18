#include "minunit.h"
#include <grafx/grafx.h>

char *test_test()
{
    
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_test);

    return NULL;
}

RUN_TESTS(all_tests);


