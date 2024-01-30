#ifndef _grafx_camera
#define _grafx_camera

#include "grafx.h"

typedef struct {
    GFX_Entity base;
    GFX_Buffer *buffer;
    GFX_Stage *stage;
    Uint32 width;               // horizontal size of the camera render
    Uint32 height;              // vertical size of the camera render

} GFX_Camera;

#endif