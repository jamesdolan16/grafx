/* #include "console.h"

static GFX_Console *ConsoleCreate()
{
    return (GFX_Console *)calloc(1, sizeof(GFX_Console));
}

GFX_Console *GFX_ConsoleConstruct(const_bstring id, GFX_Buffer *draw_buffer)
{
    check(draw_buffer != NULL, "Null draw buffer provided");

    GFX_Console *console = ConsoleCreate();
    check_mem(console);

    console->command_buffer = List_create();
    check_mem(console->command_buffer);

    console->font = TTF_OpenFont(DEFAULT_FONT, DEFAULT_FONT_SIZE);
    check_sdl_ptr(console->font);

    console->fg_color = (SDL_Color){255, 255, 255, SDL_ALPHA_OPAQUE};
    console->bg_color = (SDL_Color){0, 0, 0, 200};     // Translucent black looks nice, I imagine

    console->draw_buffer = draw_buffer;
    console->visible = SDL_FALSE;

    return console;
error:
    if(console->command_buffer) List_clear_destroy(console->command_buffer);
    if(console) free(console);
    return NULL;
}

void GFX_ConsoleDestruct(GFX_Console *console)
{
    check(console != NULL, "Null console provided");

    List_clear_destroy(console->command_buffer);
    free(console);

error:
    return;
}

GFX_ERROR_CODE GFX_ConsoleSetVisible(GFX_Console *console, SDL_bool visible)
{
    check(console != NULL, "Null console provided");

    console->visible = visible;

    return GFX_EC_NOERROR;
error:
    return GFX_EC_NULLPTR;
}

GFX_ERROR_CODE GFX_ConsoleListen(GFX_Console *console)
{
    check_ptr(console != NULL, "Null console provided");

    bstring composition;
    bstring input_buffer;
    SDL_bool finished = SDL_FALSE;
    Sint32 cursor;
    Sint32 selection_length;
    int rc;
    GFX_ERROR_CODE ec;

    SDL_StartTextInput();
    while(!finished){
        SDL_Event event;
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    finished = SDL_TRUE;
                    break;  
                case SDL_TEXTINPUT:
                    rc = bcatcstr(input_buffer, event.text.text);
                    check(rc == BSTR_OK, "Failed to cat text input");
                    break;
                case SDL_TEXTEDITING:
                    rc = bassigncstr(composition, event.edit.text);
                    check(rc == BSTR_OK, "Failed to assign text composition");
                    cursor = event.edit.start;
                    selection_length = event.edit.length;
                    break;       
            }
        }

        ec = GFX_ConsoleExecute(console->command_buffer, input_buffer);
        check(ec == GFX_EC_NOERROR, "Failed to execute provided command");

        ec = ConsoleRender();
        check(ec == GFX_EC_NOERROR, "Failed to render console");
    }

    return GFX_EC_NOERROR;
error:
    return GFX_EC_ERROR;
nullptr:
    return GFX_EC_NULLPTR;
}

GFX_ERROR_CODE GFX_ConsoleExecute(GFX_Console *console, const_bstring command)
{
    List_unshift(console->command_buffer, command);

    return GFX_EC_NOERROR;
}

static GFX_ERROR_CODE ConsoleRender(GFX_Console *console)
{
    char *render_cstr;
    bstring render_bstr;

    for(ListNode *command = console->command_buffer->first; 
        command->next != NULL; command = command->next){
        bconcat(render_bstr, (const_bstring)command->value);
    }

    render_cstr = bstr2cstr(render_bstr, '\0');

    SDL_Surface *surface = TTF_RenderText_Solid(console->font, render_cstr, 
                                                console->fg_color);
}
 */