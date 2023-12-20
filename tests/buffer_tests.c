#include "minunit.h"

#include <grafx/buffer.h>

GFX_Buffer *test_buffer;

char *test_BufferConstruct()
{
    test_buffer = GFX_BufferConstruct(bfromcstr("test_buffer_1"),
                                        60, 60, 
                                        SDL_PIXELFORMAT_ARGB8888);
    mu_assert((test_buffer), "Failed to allocate GFX_Buffer, got NULL pointer.");
    mu_assert(test_buffer->height == 60, "Failed to set basic attribute.");
    mu_assert((test_buffer->pixels), "Failed to allocate GFX_Buffer.pixels.");
    for(size_t row = 0; row < test_buffer->height; row++){
        mu_assert((test_buffer->pixels[row]), "Failed to allocate row.");
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_BufferConstruct);
    mu_run_test(test_BufferDestroy);
    return NULL;
}

RUN_TESTS(all_tests);
