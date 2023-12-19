#ifndef _grafx_panel_h
#define _grafx_panel_h

#include <SDL2/SDL.h>

#include "bstrlib.h"

typedef struct {
    Uint32 width;
    Uint32 height;
    Uint32 x;
    Uint32 y;
    GFX_Buffer *buffer;
} GFX_Panel;

GFX_Panel *GFX_PanelConstruct(const_bstring id, GFX_Buffer *buffer,
                    Uint32 width, Uint32 height, Uint32 x, Uint32 y);

void GFX_PanelDestroy(GFX_Panel *panel);

GFX_ERROR_CODE GFX_PanelRender(SDL_Renderer *renderer);

#endif