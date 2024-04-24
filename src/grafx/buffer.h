#ifndef _grafx_buffer_h
#define _grafx_buffer_h

#include <SDL2/SDL.h>

#include "bstrlib.h"
#include "dbg.h"
#include "error_code.h"

/**
 * Object to store pixel buffers. Used in conjunction with 
*/
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

/**
 * Set all the pixels in the provided buffer to 0
*/
GFX_ERROR_CODE GFX_BufferClear(GFX_Buffer *buffer);

#endif