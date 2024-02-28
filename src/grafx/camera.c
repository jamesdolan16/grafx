#include "camera.h"

static GFX_Camera *CameraCreate()
{
    return (GFX_Camera *)calloc(1, sizeof(GFX_Camera));
}

GFX_Camera *GFX_CameraConstruct(const_bstring id, float pos_x, float pos_y, float pos_h,
                                GFX_Angle pos_a, GFX_Buffer *buffer, GFX_Stage *stage,
                                Uint32 width, Uint32 height)
{
    check(buffer != NULL, "Null buffer provided.");
    check(stage != NULL, "Null stage provided.");
    check(width > 0, "Width must be greater than 0.");
    check(height > 0, "Height must be greater than 0.");

    GFX_Camera *camera = CameraCreate();
    check_mem(camera);

    camera->base = (GFX_Entity){ .id = id, .x = pos_x, .y = pos_y, .h = pos_h, .angle = pos_a };
    camera->buffer = buffer;
    camera->stage = stage;
    camera->z_buffer = (double *)calloc(width, sizeof(double));
    camera->width = width;
    camera->height = height;

    return camera;
error:
    return NULL;
}

void GFX_CameraDestroy(GFX_Camera *camera)
{
    check(camera != NULL, "Null camera provided.");
    free(camera);
error:
}

GFX_ERROR_CODE GFX_CameraRender(GFX_Camera *camera)
{
    GFX_ERROR_CODE ec = CalculateCameraPlaneVec2(camera);
    GFX_Vec2 dVec2 = GFX_Vec2FromAngle(camera->base.angle);

    double time = 0, old_time = 0;  // Time of current and previous frame

    // Cast floor and ceiling first
    for(Uint32 y = 0; y < camera->height; y++){
        // raydir for leftmost ray (x = 0) and rightmost (x = camera->width)
        double raydir_x0 = dVec2.x - camera->plane.x;
        double raydir_y0 = dVec2.y - camera->plane.y;
        double raydir_x1 = dVec2.x + camera->plane.x;
        double raydir_y1 = dVec2.y + camera->plane.y;

        int p = y - camera->height / 2;     // Current y position compared to the center of the screen (the horizon)

        camera->base.h = camera->height / 2;    // Vertical position of the camera TODO: Figure out if this needs to be here

        // horizontal distance from the camera to the floor for the current row
        // 0.5 is the z-position exactly in the middle between floor and ceiling
        double row_distance = camera->base.h / p;

        // calculate the real world step vector we have to add for each x (parallel to camera plane)
        // adding step by step avoids multiplications with a weight in the inner loop
        double floor_step_x = row_distance * (raydir_x1 - raydir_x0) / camera->width;
        double floor_step_y = row_distance * (raydir_y1 - raydir_y0) / camera->width;

        // real world coordinates of leftmost column. This will be updated as we step to the right
        double floor_x = camera->base.x + row_distance * raydir_x0;
        double floor_y = camera->base.y + row_distance * raydir_y0;

        for(Uint32 x = 0; x < camera->width; ++x){
            // the cell coord is simply got from the integer parts of floorX and floorY
            int cell_x = (int)(floor_x);
            int cell_y = (int)(floor_y);

            // get the texture coordinate from the fractional part
            int tx = (int)(GFX_TILE_WIDTH * (floor_x - cell_x)) & (GFX_TILE_WIDTH - 1);
            int ty = (int)(GFX_TILE_WIDTH * (floor_y - cell_y)) & (GFX_TILE_WIDTH - 1);

            floor_x += floor_step_x;
            floor_y += floor_step_y;

            GFX_TileType tt = camera->stage->tilemap->tiles[(int)camera->base.x][(int)camera->base.y]->tiletype;

            Uint32 colour = ((Uint32 *)tt.surface->pixels)[GFX_TILE_WIDTH * ty + tx];   // Floor
            colour = (colour >> 1) & 8355711;   // Make it darker
            camera->buffer->pixels[y][x] = colour;

            camera->buffer->pixels[camera->height - y - 1][x] = colour;     // ceiling (symmetrical, at screenheight - y - 1 instead of 1)
        }
    }

    // Cast walls
    for(Uint32 x = 0; x < camera->width; ++x){
        // Calculate ray position and direction
        double camera_x = 2 * x / (double)camera->width - 1;    // x coordinate in camera space

        GFX_Vec2 raydir = { .x = dVec2.x + camera->plane.x * camera_x,
                            .y = dVec2.y + camera->plane.y * camera_x };

        // Which box of the map we're in
        int map_x = (int)camera->base.x;
        int map_y = (int)camera->base.y;

        double side_dist_x, side_dist_y;    // Length of ray from current position to next x or y side

        // Length of ray to step a single tile in respective directions
        double delta_dist_x = fabs(1 / raydir.x);
        double delta_dist_y = fabs(1 / raydir.y);
        double p_wall_dist;     // Distance to perpendicular wall

        GFX_Vec2 step;

        SDL_bool hit_wall = SDL_FALSE;
        SDL_bool vertical_hit;

        // calculate step and intiial side_dist
        if(raydir.x < 0){
            step.x = -1;
            side_dist_x = (camera->base.x - map_x) * delta_dist_x;
        } else {
            step.x = 1;
            side_dist_x = (map_x + 1.0 - camera->base.x) * delta_dist_x;
        }

        if(raydir.y < 0){
            step.y = -1;
            side_dist_y = (camera->base.y - map_y) * delta_dist_y;
        } else {
            step.y = 1;
            side_dist_y = (map_y + 1.0 - camera->base.y) * delta_dist_y;
        }

        // perform DDA
        while(!hit_wall){
            // jump to next map tile either in x-direction or y-direction
            if(side_dist_x < side_dist_y){
                side_dist_x += delta_dist_x;
                map_x += step.x;
                vertical_hit = SDL_FALSE;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step.y;
                vertical_hit = SDL_TRUE;
            }

            if(camera->stage->tilemap->tiles[map_x][map_y]->tiletype->is_solid){
                hit_wall = SDL_TRUE;
            }
        }

        // calulate the distance from wall to camera plane
        if(!vertical_hit) p_wall_dist = (side_dist_x - delta_dist_x);
        else p_wall_dist = (side_dist_y - delta_dist_y);

        // calculate the height of the line to draw on screen
        int line_height = (int)camera->height / p_wall_dist;

        // calculate the limits of the current line
        int draw_start = -line_height / 2 + camera->height / 2;
        if(draw_start < 0) draw_start = 0;

        int draw_end = line_height / 2 + camera->height / 2;
        if(draw_end > camera->height) draw_end = camera->height - 1;

        SDL_Surface *texture = camera->stage->tilemap->tiles[map_x][map_y]->tiletype->surface;

        // calculate value of wall_x
        double wall_x;  // where exactly the wall was hit
        if(!vertical_hit) wall_x = camera->base.y + p_wall_dist * raydir.y;
        else wall_x = camera->base.x + p_wall_dist * raydir.x;
        wall_x -= floor(wall_x);
        
        // x-coordinate on the texture
        int tex_x = (int)(wall_x * (double)texture->w);
        if(!vertical_hit && raydir.x > 0) tex_x = texture->w - tex_x - 1;
        if(vertical_hit && raydir.y < 0) tex_x = texture->w - tex_x - 1;

        // how much to increase the texture coordinate per screen pixel
        double c_step = 1.0 * texture->h / line_height;

        // starting texture coordinate
        double tex_pos = (draw_start - camera->height / 2 + line_height / 2) * c_step;
        for(int y = draw_start; y < draw_end; y++){
            // cast the texture coordinate to integer and mask with (tex_height - 1) in case of overflow
            int tex_y = (int)tex_pos & (texture->h - 1);
            tex_pos += c_step;
            Uint32 p_colour = ((Uint32 *)texture->pixels)[texture->h * tex_y + tex_x];
            // make colour darker for y-sides: RGB bytes divided by 2 then anded with this magic number
            if(vertical_hit) p_colour = (p_colour >> 1) & 835571;
            camera->buffer->pixels[y][x] = p_colour;
        }

        // set the z_buffer for sprite casting
        camera->z_buffer[x] = p_wall_dist;
    }

    // sprite casting
    // calculate distance of each sprite from camera
    for(int i = 0; i < DArray_count(camera->stage->sprites); i++){
        GFX_Sprite *sprite = (GFX_Sprite *)DArray_get(camera->stage->sprites, i);
        // Do a bit of pythagoras but dont bother sqrt'ing the hypotenuse as were just using the value to sort
        sprite->distance = ((camera->base.x - sprite->base.x) * (camera->base.x - sprite->base.x)
                            + (camera->base.y - sprite->base.y) * (camera->base.y - sprite->base.y));
    }
    DArray_qsort(camera->stage->sprites, SortSpritesByDistance);

    // project sprites and draw them
    for(int i = 0; i < DArray_count(camera->stage->sprites); i++){
        GFX_Sprite *sprite = DArray_get(camera->stage->sprites, i);
        double sprite_x = sprite->base.x - camera->base.x;
        double sprite_y = sprite->base.y - camera->base.y;

        // transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]

        // inverse determinant
        double inv_det = 1.0 / (camera->plane.x * dVec2.y - dVec2.x * camera->plane.y);    // required for correct matrix multiplication

        double transform_x = inv_det * (dVec2.y * sprite_x - dVec2.x * sprite_y);
        double transform_y = inv_det * (-camera->plane.y * sprite_x + camera->plane.x * sprite_y);  // this is the depth inside the screen, Z coordinate in true 3D

        int sprite_screen_x = (int)((camera->width / 2) * (1 + transform_x / transform_y));

        int v_pos_screen = (int)(sprite->v_pos / transform_y);

        // calcualate the height of the sprite on screen
        int sprite_height = abs((int)(camera->height / transform_y)) / sprite->v_scale; // using transform_y instead of the real distance prevents fisheye

        // calculate the lowest and heightest pixels to fill in current stripe
        int draw_start_y = -sprite_height / 2 + camera->height / 2 + v_pos_screen;
        if(draw_start_y < 0) draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + camera->height / 2 + v_pos_screen;
        if(draw_end_y > camera->height) draw_end_y = camera->height - 1;

        // calculate the width of the sprite
        int sprite_width = abs((int)(camera->height / transform_y)) / sprite->v_scale;
        
        int draw_start_x = -sprite_width / 2 + sprite_screen_x;
        if(draw_start_x < 0) draw_start_x = 0;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;
        if(draw_end_x >= camera->width) draw_end_x = camera->width - 1;

        // loop through every vertical stripe of the sprite on screen
        for(int stripe = draw_start_x; stripe < draw_end_x; stripe++){
            int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
                                * GFX_TILE_WIDTH / sprite_width) / 256;
            /** the conditions in the if are
             * 1. it's in front of camera plane so you don't see things behind you
             * 2. it's on the screen (left)
             * 3. it's on the screen (right)
             * 4. z_buffer, with perpendicular distance
            */ 
            if(transform_y > 0 && stripe > 0 && stripe < camera->width 
                && transform_y < camera->z_buffer[stripe])
            {
                for(int y = draw_start_y; y < draw_end_y; y++){
                    int d = (y - sprite->v_pos) * 256 - camera->height * 128 + sprite_height * 128; // 256 and 128 to avoid floats
                    int tex_y = ((d * GFX_TILE_WIDTH) / sprite_height) / 256;
                    Uint32 p_colour = ((Uint32 *)(sprite->texture->pixels))[sprite->texture->h * tex_y + tex_x];
                    if((p_colour & 0x00FFFFFF) != 0) camera->buffer->pixels[y][stripe] = p_colour;  // paint pixel if it isnt black, black is the invisible colour
                }
            }
        }
    }
}

/**
 * Sorts the sprites in reverse order by distance (farthest first)
*/
static int SortSpritesByDistance(const void *a, const void *b)
{
    if(((GFX_Sprite *)a)->distance > ((GFX_Sprite *)b)->distance) return -1;
    if(((GFX_Sprite *)b)->distance < ((GFX_Sprite *)b)->distance) return 1;
    else return 0;
}

/**
 * Calculate the camera plane vector by shifting the camera angle (direction) a
 * quarter-turn (pi/2 or 90deg) and then converting the new angle to a vec2.
*/
static GFX_ERROR_CODE CalculateCameraPlaneVec2(GFX_Camera *camera)
{
    camera->plane = GFX_Vec2FromAngle(GFX_AngleRightAngle(camera->base.angle));
}