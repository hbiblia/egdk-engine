#include "pixel-transform.h"

rtransform trans_default(void)
{
    rtransform t = {0};

    t.scale = (rvect3){1.0f, 1.0f, 1.0f};
    t.pivot = (rvect2){0.5f, 0.5f};

    return t;
}
