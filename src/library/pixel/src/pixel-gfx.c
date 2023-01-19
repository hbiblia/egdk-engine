#include "pixel-gfx.h"
#include "pixel.h"

#include <epoxy/gl.h>

// #define SOKOL_GLES2
#define SOKOL_GLCORE33

#define SOKOL_IMPL
#define SOKOL_GFX_IMPL
#define SOKOL_EXTERNAL_GL_LOADER
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"
#include "sokol/sokol_time.h"

