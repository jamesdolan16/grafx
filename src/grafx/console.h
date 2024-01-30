/* #ifndef _grafx_console_h
#define _grafx_console_h

#include "bstrlib.h"
#include "buffer.h"
#include "error_code.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <lcthw/list.h>

#define DEFAULT_FONT "bin/UbuntuMono-R.ttf"
#define DEFAULT_FONT_SIZE 16

typedef struct {
    List *command_buffer;       // List of previously executed commands starting with the most recent    
    GFX_Buffer *draw_buffer;
    TTF_Font *font;
    SDL_Color fg_color, bg_color;
    SDL_bool visible;
} GFX_Console;

GFX_Console *GFX_ConsoleConstruct(const_bstring id, GFX_Buffer *draw_buffer);
void GFX_ConsoleDestruct(GFX_Console *console);

GFX_ERROR_CODE GFX_ConsoleSetVisible(GFX_Console *console, SDL_bool visible);

GFX_ERROR_CODE GFX_ConsoleListen(GFX_Console *console);

GFX_ERROR_CODE GFX_ConsoleExecute(GFX_Console *console, const_bstring command);

#endif */