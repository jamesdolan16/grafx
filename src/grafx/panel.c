#include "panel.h"

static GFX_Panel *PanelCreate()
{
    GFX_Panel *panel = (GFX_Panel *)calloc(1, sizeof(panel));
    return panel;
}

GFX_Panel *GFX_PanelConstruct(SDL_Renderer *renderer, const_bstring id, GFX_Buffer *buffer, 
                            Uint32 width, Uint32 height, Uint32 x, Uint32 y)
{
    check(renderer != NULL, "Null renderer provided.");
    check(buffer != NULL, "Null buffer provided.");
    GFX_Panel *panel = PanelCreate();
    check_mem(panel);

    SDL_Texture *texture = SDL_CreateTexture(renderer, buffer->sdl_pixel_format,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            width, height);
    check_sdl_ptr(texture);

    *panel = (GFX_Panel){.width=width, .height=height, .x=x, .y=y, .buffer=buffer, 
                        .texture=texture, .renderer=renderer};

    return panel;

error:
    if(panel)   free(panel);
    return NULL;
}

void GFX_PanelDestroy(GFX_Panel *panel)
{
    check(panel != NULL, "Null panel provided.");
    
    GFX_BufferDestroy(panel->buffer);
    free(panel);

error:
}

GFX_ERROR_CODE GFX_PanelRender(GFX_Panel *panel)
{
    check_mem(panel);

    int rc = SDL_UpdateTexture(panel->texture, NULL, panel->buffer->pixels, 
                        panel->width * sizeof(Uint32));
    check_sdl_rc(rc);

    rc = SDL_RenderCopy(panel->renderer, panel->texture, NULL, NULL);
    check_sdl_rc(rc);

    GFX_BufferClear(panel->buffer);

    return GFX_EC_NOERROR;
error: 
    return GFX_EC_ERROR;
}
