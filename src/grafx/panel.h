#ifndef _grafx_panel_h
#define _grafx_panel_h

#include <SDL2/SDL.h>

#include "bstrlib.h"
#include "buffer.h"
#include "error_code.h"

typedef struct {
    Uint32 width;
    Uint32 height;
    Uint32 x;
    Uint32 y;
    GFX_Buffer *buffer;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
} GFX_Panel;

GFX_Panel *GFX_PanelConstruct(SDL_Renderer *renderer, const_bstring id, GFX_Buffer *buffer,
                            Uint32 width, Uint32 height, Uint32 x, Uint32 y);

void GFX_PanelDestroy(GFX_Panel *panel);

GFX_ERROR_CODE GFX_PanelRender(GFX_Panel *panel);

#endif