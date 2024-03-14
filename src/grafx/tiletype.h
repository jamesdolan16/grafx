#ifndef _grafx_tiletype_h
#define _grafx_tiletype_h

#include "bstrlib.h"
#include "dbg.h"

#include <SDL2/SDL.h>

typedef struct {
    const_bstring id;
    SDL_Surface *surface;
    SDL_bool is_solid;    
} GFX_TileType;

GFX_TileType *GFX_TileTypeConstruct(const_bstring id, SDL_Surface *surface,
                                    SDL_bool is_solid);

void GFX_TileTypeDestroy(GFX_TileType *tiletype);

#endif