#ifndef _gfrax_error_code_h
#define _gfrax_error_code_h

typedef enum {
    GFX_EC_NOERROR,
    GFX_EC_ERROR,
    GFX_EC_NULLPTR
} GFX_ERROR_CODE;

inline void *check_sdl_rc(int rc)
{
    check(rc == 0, "%s", SDL_GetError());
}

inline void *check_sdl_ptr(void *ptr)
{
    check(ptr != NULL, "%s", SDL_GetError());
}

#endif