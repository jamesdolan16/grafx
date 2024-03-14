#include "textbox.h"

static GFX_TextBox *TextBoxCreate(void)
{
    return (GFX_TextBox *)(calloc(1, sizeof(GFX_TextBox)));
}

GFX_TextBox *GFX_TextBoxConstruct(Uint16 x, Uint16 y, Uint16 w, Uint16 h, 
                                    SDL_bool fit_content, SDL_Color fg_colour, 
                                    SDL_Color bg_colour, GFX_Panel *panel, 
                                    TTF_Font *font)
{
    check(panel != NULL, "Null panel provided.");
    check(font != NULL, "Null ttf_font provided.");

    GFX_TextBox *textbox = TextBoxCreate();
    check_mem(textbox);

    *textbox = (GFX_TextBox){ .x=x, .y=y, .w=w, .h=h, 
                            .fit_content=fit_content, .fg_colour=fg_colour, 
                            .bg_colour=bg_colour, .text="placeholder", .panel=panel, .font=font };

    return textbox;
error:
    return NULL;
}

GFX_ERROR_CODE GFX_TextBoxDestroy(GFX_TextBox *textbox)
{
    check(textbox != NULL, "Null textbox provided.");
    free(textbox);

    return GFX_EC_NOERROR;
error:
    return GFX_EC_NULLPTR;
}

GFX_ERROR_CODE GFX_TextBoxRender(GFX_TextBox *textbox)
{
    SDL_Surface *surface = TTF_RenderText_Solid(textbox->font, textbox->text, textbox->fg_colour);
    check_sdl_ptr(surface);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(textbox->panel->renderer, surface);         
    check_sdl_ptr(texture);

    Uint16 rect_w, rect_h;
    if(textbox->fit_content){
        rect_w = surface->w;
        rect_h = surface->h;
    } else {
        rect_w = textbox->w;
        rect_h = textbox->h;
    }

    SDL_Rect rect = { .h=rect_h, .w=rect_w, .x=textbox->x, .y=textbox->y };
    int rc = SDL_RenderCopy(textbox->panel->renderer, texture, NULL, &rect);
    check_sdl_rc(rc);

    return GFX_EC_NOERROR;
error:
    return GFX_EC_ERROR;
}