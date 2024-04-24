#include "minunit.h"

#include <grafx/grafx.h>

GFX_Panel *panel;
GFX_Buffer *buffer;
SDL_Window *window;
SDL_Renderer *renderer;


void setup()
{   
    window = SDL_CreateWindow("panel_tests", 0, 0, 64, 64, 
                                SDL_WINDOW_HIDDEN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    buffer = GFX_BufferConstruct(bfromcstr("test_buffer"), 64, 64, 
                                    SDL_PIXELFORMAT_ARGB8888);
}

void teardown()
{
    GFX_BufferDestroy(buffer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

char *test_PanelConstruct()
{
    panel = GFX_PanelConstruct(renderer, bfromcstr("panel_tests"), buffer,
                                buffer->width, buffer->height, 0, 0);
    mu_assert((panel), "Failed to allocate GFX_Panel.");
    mu_assert((panel->texture), "Failed to allocate GFX_Panel.texture");
    return NULL;
}

char *test_PanelRender()
{
    GFX_ERROR_CODE rc = GFX_PanelRender(panel);
    mu_assert(rc == 0, "Failed to render GFX_Panel due to SDL Error");

    return NULL;
}

char *all_tests()
{
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init Error: %s\n", SDL_GetError());
    setup();

    mu_suite_start();

    mu_run_test(test_PanelConstruct);
    mu_run_test(test_PanelRender);

    teardown();

error:
    return NULL;
}

RUN_TESTS(all_tests);