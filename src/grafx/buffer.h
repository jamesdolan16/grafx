#ifndef _grafx_buffer_h
#define _grafx_buffer_h

#include <SDL2/SDL.h>

#include "bstrlib.h"
#include "dbg.h"
#include "error_code.h"

typedef struct {
    Uint32 width;
    Uint32 height;
    Uint32 *pixels;
    SDL_PixelFormatEnum sdl_pixel_format_enum;
    SDL_PixelFormat *sdl_pixel_format;
} GFX_Buffer;

GFX_Buffer *GFX_BufferConstruct(const_bstring id, Uint32 width, Uint32 height,
                                Uint32 sdl_pixel_format);

GFX_ERROR_CODE GFX_BufferDestroy(GFX_Buffer *buffer);

GFX_ERROR_CODE GFX_BufferClear(GFX_Buffer *buffer);

#endif