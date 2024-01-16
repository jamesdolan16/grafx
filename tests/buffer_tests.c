#include "minunit.h"

#include <grafx/buffer.h>

GFX_Buffer *test_buffer;

char *test_BufferConstruct()
{
    bstring id = bfromcstr("test_buffer_1");
    test_buffer = GFX_BufferConstruct(id,60, 60, 
                                        SDL_PIXELFORMAT_ARGB8888);
    mu_assert((test_buffer), "Failed to allocate GFX_Buffer, got NULL pointer");
    mu_assert(test_buffer->height == 60, "Failed to set basic attribute");
    mu_assert((test_buffer->pixels), "Failed to allocate GFX_Buffer.pixels");
    for(Uint32 row = 0; row < test_buffer->height; row++){
        mu_assert((test_buffer->pixels[row]), "Failed to allocate row");
    }

    bdestroy(id);

    return NULL;
}

char *test_BufferClear()
{
    GFX_BufferClear(test_buffer);
    for(Uint32 row = 0; row < test_buffer->height; row++){
        for(Uint32 column = 0; column < test_buffer->width; column++){
            mu_assert(test_buffer->pixels[row][column] == 0, 
                        "Failed to clear all GFX_Buffer.pixels");
        }
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_BufferConstruct);
    mu_run_test(test_BufferClear);

    return NULL;
}

RUN_TESTS(all_tests);
