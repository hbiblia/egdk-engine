#include "ui-docked-inspector.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"
#include "single-file.h"

static EditorSingleFile *single;

static void inspector_component_props_draw(const char *name, const void *ptr, ecs_entity_t component);

void editor_gui_inspector_init(void)
{
    single = eSingleFile_Get();
}

void editor_gui_inspector_draw(void)
{
    ecs_entity_t selected = single->entity_selected;

    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
        if (!pEcs_EntityIsValid(selected))
        {
            igTextWrapped("Select anything to Inspect");
        }
        else
        {
            ecs_type_t *type = pEcs_EntityGetType(selected);

            for (int i = 0; i < type->count; i++)
            {
                ecs_id_t id = type->array[i];
                ecs_entity_t component = ecs_pair_second(pEcs_World(), id);
                const void *component_ptr = ecs_get_id(pEcs_World(), selected, component);
                if (!component_ptr)
                    continue;

                const char *name_cmp = ecs_get_name(pEcs_World(), component);
                // -------------------------------------
                // Cargamos las propiedades de los componentes
                // -------------------------------------
                inspector_component_props_draw(name_cmp, component_ptr, component);
            }

            // -------------------------------------
            // Boton para agregar mas componentes
            // -------------------------------------
            igPushItemWidth(-1);
            {
                float WindowWidth = igGetWindowWidth();
                if (igButton("+ Component", (ImVec2){WindowWidth - 15, 0}))
                {
                }
                igPopItemWidth();
            }
        }
    }
    igEnd();
}

void inspector_component_props_draw(const char *name, const void *ptr, ecs_entity_t component)
{
    const ImGuiTreeNodeFlags flags_treenode = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

    igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){4.0f, 4.0f});

    float lineHeight = igGetFontSize() + igGetStyle()->FramePadding.y * 2.0f;
    bool bopen = igTreeNodeEx_Str(name, flags_treenode);
    {
        igPopStyleVar(1);

        if (bopen)
        {
            igTreePop();
        }
    }
}
