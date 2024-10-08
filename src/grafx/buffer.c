#include "buffer.h"

static GFX_Buffer *BufferCreate()
{
    GFX_Buffer *buffer = (GFX_Buffer *)calloc(1, sizeof(GFX_Buffer));
    
    return buffer;
}

/**
 * Creates a GFX_Buffer with the provided attributes
*/
GFX_Buffer *GFX_BufferConstruct(const_bstring id, Uint32 width, Uint32 height, 
                            SDL_PixelFormatEnum sdl_pixel_format)
{
    Uint32 *pixels = NULL;

    GFX_Buffer *buffer = BufferCreate();
    check_mem(buffer);

    pixels = calloc(height, sizeof(Uint32) * width * height);
    check_mem(pixels);

    SDL_PixelFormat* pixel_format = SDL_AllocFormat(sdl_pixel_format);
    check_sdl_ptr(pixel_format);

    *buffer = (GFX_Buffer){.width=width, .height=height, .pixels=pixels, 
                            .sdl_pixel_format_enum=sdl_pixel_format,
                            .sdl_pixel_format=pixel_format};

    return buffer;

error:
    if(pixels)  free(pixels);
    if(buffer)  GFX_BufferDestroy(buffer);

    return NULL;
}

/**
 * Destroys the provided GFX_Buffer
*/
GFX_ERROR_CODE GFX_BufferDestroy(GFX_Buffer *buffer)
{
    check(buffer != NULL, "Null buffer provided.");

    free(buffer->pixels);
    buffer->pixels = NULL;
    free(buffer);

    return GFX_EC_NOERROR;
error:
    return GFX_EC_NULLPTR;
}

/**
 * Clears all the pixel data in the buffer
*/
GFX_ERROR_CODE GFX_BufferClear(GFX_Buffer *buffer)
{
    check(buffer != NULL, "Null buffer provided.");

    for(Uint32 row = 0; row < buffer->height; row++){
        for(Uint32 column = 0; column < buffer->width; column++){
            buffer->pixels[row + (buffer->width * column)] = 0xFF000000;
        }
    }

    return GFX_EC_NOERROR;
error:
    return GFX_EC_NULLPTR;
}