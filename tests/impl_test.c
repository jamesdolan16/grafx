#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <grafx/grafx.h>

#define SCREENWIDTH 1000
#define SCREENHEIGHT 700

#define MAPWIDTH 24
#define MAPHEIGHT 24

SDL_Window *window;
SDL_Renderer *renderer;

int worldMap[MAPWIDTH][MAPHEIGHT] =
{
    {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
    {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
    {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
    {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
    {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
    {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
    {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
    {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
    {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
    {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
    {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
    {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Implementation Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, 0);
    check_sdl_ptr(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int ec = TTF_Init(); 
    check_sdl_rc(ec);

    TTF_Font *font = TTF_OpenFont("resources/fonts/UbuntuMono-R.ttf", 16);
    check_sdl_ptr(font);

    GFX_Buffer *buffer = GFX_BufferConstruct(NULL, 20, 20, SDL_PIXELFORMAT_ARGB8888);

    GFX_Panel *panel = GFX_PanelConstruct(renderer, NULL, buffer, 20, 20, 0, 0);
    GFX_TileMap *tilemap = GFX_TileMapFromIntArray(worldMap, MAPWIDTH, MAPHEIGHT);
    GFX_Stage *stage = GFX_StageContruct(NULL, buffer, tilemap);
    GFX_Camera *camera = GFX_CameraConstruct(NULL, 22, 11.5, 0, GFX_AngleFromRad(0.0), buffer, stage, 20, 20);


    int close = 0;
    double time = 0, oldTime = 0;   // time of current frame and previous frame

    SDL_Event event;
    SDL_Colour colour = { 0, 255, 255, 255 };
    GFX_TextBox *textbox = GFX_TextBoxConstruct(0, 0, 200, 50, true, colour, colour, panel, font);

    while(!close){
        ec = SDL_RenderClear(renderer);
        check_sdl_rc(ec);
        
        ec = GFX_CameraRender(camera);
        //ec = GFX_TextBoxRender(textbox);
        GFX_PanelRender(panel);

        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;
        sprintf(textbox->text, "posX: %f posY: %f fps: %f debug: %s", camera->base.x, camera->base.y, frameTime, SDL_GetError());

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_PollEvent(&event);
        SDL_Delay(8);
    }

    /*GFX_CameraDestroy(camera);
    GFX_StageDestroy(stage);
    GFX_TileMapDestroy(tilemap);
    GFX_PanelDestroy(panel);
    GFX_BufferDestroy(buffer);
*/
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
error:
    return 0;
}