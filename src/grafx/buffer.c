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
                            Uint32 sdl_pixel_format)
{
    int row = 0;
    Uint32 **pixels = NULL;

    GFX_Buffer *buffer = BufferCreate();
    check_mem(buffer);

    pixels = calloc(height, sizeof(Uint32 *));
    check_mem(pixels);
    for(row = 0; row < height; row++){
        pixels[row] = (Uint32 *)calloc(width, sizeof(Uint32));
        check_mem(pixels[row]);
    }

    *buffer = (GFX_Buffer){.width=width, .height=height, .pixels=pixels, 
                            .sdl_pixel_format=sdl_pixel_format};

    return buffer;

error:
    for( ; row >= 0; row--){   
        free(pixels[row]);
    }
    if(pixels)  free(pixels);
    if(buffer)  GFX_BufferDestroy(buffer);

    return NULL;
}

/**
 * Destroys the provided GFX_Buffer
*/
void GFX_BufferDestroy(GFX_Buffer *buffer)
{
    if(buffer){
        for(Uint32 row = 0; row < buffer->height; row++){
            free(buffer->pixels[row]);
            buffer->pixels[row] = NULL;
        }
        free(buffer->pixels);
        buffer->pixels = NULL;
        free(buffer);
    }
}