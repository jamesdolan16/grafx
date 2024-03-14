#ifndef _grafx_textbox_h
#define _grafx_textbox_h

#define TEXTBOX_MAX_LEN 256

#include "bstrlib.h"
#include "panel.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    Uint16 x;
    Uint16 y;
    Uint16 w;
    Uint16 h;
    SDL_bool fit_content;
    SDL_Color fg_colour;
    SDL_Color bg_colour;
    char text[TEXTBOX_MAX_LEN];     // Text buffer of size TEXTBOX_MAX_LEN
    GFX_Panel *panel;
    TTF_Font *font;
} GFX_TextBox;

GFX_TextBox *GFX_TextBoxConstruct(Uint16 x, Uint16 y, Uint16 w, Uint16 h, 
                                    SDL_bool fit_content, SDL_Color fg_colour, 
                                    SDL_Color bg_colour, GFX_Panel *panel, 
                                    TTF_Font *font);

GFX_ERROR_CODE GFX_TextBoxDestroy(GFX_TextBox *textbox);

GFX_ERROR_CODE GFX_TextBoxRender(GFX_TextBox *textbox);

#endif