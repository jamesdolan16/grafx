#ifndef _grafx_camera_h
#define _grafx_camera_h

#define FLOORTEX 6
#define CEILTEX 5

#include <lcthw/darray_algos.h>

#include "entity.h"
#include "buffer.h"
#include "stage.h"
#include "vec2.h"
#include "bstrlib.h"
#include "angle.h"
#include "buffer.h"
#include "sprite.h"

typedef struct {
    GFX_Entity base;
    GFX_Buffer *buffer;
    GFX_Stage *stage;
    double *z_buffer;
    Uint32 width;               // horizontal size of the camera render
    Uint32 height;              // vertical size of the camera render
    GFX_Vec2 plane;             // camera plane

} GFX_Camera;

GFX_Camera *GFX_CameraConstruct(const_bstring id, float pos_x, float pos_y, float pos_h,
                                GFX_Angle pos_a, GFX_Buffer *buffer, GFX_Stage *stage,
                                Uint32 width, Uint32 height);
                        
void GFX_CameraDestroy(GFX_Camera *camera);

/**
 * Renders a single frame for the provided camera
*/
GFX_ERROR_CODE GFX_CameraRender(GFX_Camera *camera);

#endif