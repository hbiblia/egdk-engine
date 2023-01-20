#include "pixel-texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "sokol/sokol_gfx.h"

pixel_texture_t pixel_texture_load_file(const char *filename)
{
    pixel_texture_t texture = {0};

    int comp;
    stbi_uc *data = stbi_load(filename, &texture.width, &texture.height, &comp, STBI_rgb_alpha);

    if (data != NULL)
    {
        sg_image d = sg_make_image(&(sg_image_desc){
            .width = texture.width,
            .height = texture.height,
            .data.subimage[0][0] = {
                .ptr = data,
                .size = (size_t){texture.width * texture.height * 4},
            },
        });
        texture.id = d.id;

        stbi_image_free(data);
    }

    return texture;
}


void pixel_texture_free(pixel_texture_t texture)
{
    sg_image d = (sg_image){.id = texture.id };
    sg_destroy_image(d);
}
