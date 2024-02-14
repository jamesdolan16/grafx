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
            side_dist_x = (camera->base.x) * delta_dist_x;
        }
    }
}

/**
 * Calculate the camera plane vector by shifting the camera angle (direction) a
 * quarter-turn (pi/2 or 90deg) and then converting the new angle to a vec2.
*/
static GFX_ERROR_CODE CalculateCameraPlaneVec2(GFX_Camera *camera)
{
    camera->plane = GFX_Vec2FromAngle(GFX_AngleRightAngle(camera->base.angle));
}