#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <grafx/grafx.h>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 576

#define MAPWIDTH 24
#define MAPHEIGHT 24

#define MOVESPEED 0.1
#define ROTSPEED 0.05

#define DEBOUNCEDELAY 400

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

    GFX_Buffer *buffer = GFX_BufferConstruct(NULL, SCREENWIDTH, SCREENHEIGHT, SDL_PIXELFORMAT_ARGB8888);
    
    GFX_Panel *panel = GFX_PanelConstruct(renderer, NULL, buffer, SCREENWIDTH, SCREENHEIGHT, 0, 0);
    GFX_TileMap *tilemap = GFX_TileMapFromIntArray((int *)worldMap, MAPWIDTH, MAPHEIGHT);
    GFX_Stage *stage = GFX_StageContruct(NULL, buffer, tilemap);
    GFX_Camera *camera = GFX_CameraConstruct(NULL, 1.5, 1.5, 0, GFX_AngleFromRad(GFX_PI/2), buffer, stage, SCREENWIDTH, SCREENHEIGHT);

    int close = 0;
    double time = 0, oldTime = 0;   // time of current frame and previous frame

    SDL_Event event;
    SDL_Colour colour = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    GFX_TextBox *textbox = GFX_TextBoxConstruct(0, 0, 200, 50, true, colour, colour, panel, font);

    SDL_bool paused = SDL_FALSE;
    SDL_SetRelativeMouseMode(SDL_TRUE);


    while(!close){
        if(!paused){
            ec = SDL_RenderClear(renderer);
            check_sdl_rc(ec);

            ec = GFX_CameraRender(camera);

            oldTime = time;
            time = SDL_GetTicks();
            double frameTime = (time - oldTime) / 1000.0;
            double fps = 1.0 / frameTime;
            sprintf(textbox->text, "pos x: %f pos y: %f angle: %f fps: %f debug: %s", camera->base.x, camera->base.y, camera->base.angle.value, fps, SDL_GetError());
            //printf("%s\n\n", textbox->text);

            GFX_PanelRender(panel);
            ec = GFX_TextBoxRender(textbox);

            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);            
        }
        // TODO: Replace with proper input handler
        while(SDL_PollEvent(&event)){
            double dirX, dirY, planeX, planeY;

            dirX = cos(camera->base.angle.value);
            dirY = sin(camera->base.angle.value);
            planeX = cos(GFX_AngleRightAngle(camera->base.angle).value);
            planeY = sin(GFX_AngleRightAngle(camera->base.angle).value);

            switch(event.type){
                case SDL_QUIT:
                    return 1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                            if(worldMap[(int)camera->base.y][(int)(camera->base.x + dirX * MOVESPEED)] == 0) camera->base.x += dirX * MOVESPEED;
                            if(worldMap[(int)(camera->base.y + dirY * MOVESPEED)][(int)camera->base.x] == 0) camera->base.y += dirY * MOVESPEED;
                            break;
                        case SDL_SCANCODE_S:
                            if(worldMap[(int)camera->base.y][(int)(camera->base.x - dirX * MOVESPEED)] == 0) camera->base.x -= dirX * MOVESPEED;
                            if(worldMap[(int)(camera->base.y - dirY * MOVESPEED)][(int)camera->base.x] == 0) camera->base.y -= dirY * MOVESPEED;
                            break;
                        case SDL_SCANCODE_D:
                            if(worldMap[(int)camera->base.y][(int)(camera->base.x + planeX * MOVESPEED)] == 0) camera->base.x += planeX * MOVESPEED;
                            if(worldMap[(int)(camera->base.y + planeY * MOVESPEED)][(int)camera->base.x] == 0) camera->base.y += planeY * MOVESPEED;
                            break;
                        case SDL_SCANCODE_A:
                            if(worldMap[(int)camera->base.y][(int)(camera->base.x - (planeX * MOVESPEED))] == 0) camera->base.x -= (planeX * MOVESPEED);
                            if(worldMap[(int)(camera->base.y - (planeY * MOVESPEED))][(int)camera->base.x] == 0) camera->base.y -= (planeY * MOVESPEED);
                            break;
                        case SDL_SCANCODE_Q:
                            if(paused) return 1;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            paused = !paused;
                            if(SDL_GetRelativeMouseMode())  SDL_SetRelativeMouseMode(!paused);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    camera->base.angle.value += event.motion.xrel * 0.0133f;
                    break;
            }
        }
        //SDL_Delay(5);     // Maximum number of frames will always be 120
    }

    SDL_SetRelativeMouseMode(SDL_FALSE);

    GFX_CameraDestroy(camera);
    GFX_StageDestroy(stage);
    GFX_TileMapDestroy(tilemap);
    GFX_PanelDestroy(panel);
    GFX_BufferDestroy(buffer);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
error:
    return 0;
}