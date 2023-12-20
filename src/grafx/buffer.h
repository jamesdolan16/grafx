#ifndef _grafx_buffer_h
#define _grafx_buffer_h

#include <SDL2/SDL.h>

#include "bstrlib.h"
#include "dbg.h"

typedef struct {
    Uint32 width;
    Uint32 height;
    Uint32 **pixels;
    Uint32 sdl_pixel_format;
} GFX_Buffer;

GFX_Buffer *GFX_BufferConstruct(const_bstring id, Uint32 width, Uint32 height,
                                Uint32 sdl_pixel_format);

void GFX_BufferDestroy(GFX_Buffer *buffer);

#endif