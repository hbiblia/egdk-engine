#include "ui-docked-inspector.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"
#include "single-file.h"
#include "string_fn.h"

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

void inspector_field_begin(const char *label, int id)
{
    igColumns(2, 0, false);
    igSetColumnWidth(0, 100.0f);
    igTextWrapped(label);
    igNextColumn();
    igPushItemWidth(-1);
    igPushID_Int(id);
}

void inspector_field_end(void)
{
    igPopID();
    igColumns(1, 0, false);
}

void inspector_component_props_draw(const char *name, const void *ptr, ecs_entity_t component)
{
    const ImGuiTreeNodeFlags flags_treenode = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

    igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){4.0f, 4.0f});

    char **name_split = StringSplit(name, "Component");
    const char *new_name = name_split[1];
    StringSplitFree(name_split);

    float lineHeight = igGetFontSize() + igGetStyle()->FramePadding.y * 2.0f;
    bool bopen = igTreeNodeEx_Str(new_name, flags_treenode);
    {
        igPopStyleVar(1);

        if (bopen)
        {
            ecs_meta_cursor_t cur = ecs_meta_cursor(pEcs_World(), component, ptr);

            // ----------------
            // Props UI Draws
            // ----------------
            ecs_meta_push(&cur);
            for (int i = 0; i < ECS_MEMBER_DESC_CACHE_SIZE; i++)
            {
                const char *field_name = ecs_meta_get_member(&cur);
                if (field_name == NULL)
                    break;

                // ----------------
                // type props field
                // ----------------
                inspector_field_begin(field_name, i);
                {
                    ecs_entity_t field_type = ecs_meta_get_type(&cur);
                    if (ecs_id(ecs_string_t) == field_type)
                    {
                        const char *field = ecs_meta_get_string(&cur);
                        char *buffer = String(field);
                        if (igInputText("", buffer, MAX_INPUT_TEXT, ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
                        {
                            if (strcmp(field, "Root") != 0)
                                ecs_meta_set_string(&cur, String(buffer));
                        }
                        free(buffer);
                    }
                    else if (ecs_id(ecs_bool_t) == field_type)
                    {
                        bool field = ecs_meta_get_bool(&cur);
                        if (igCheckbox("", &field))
                        {
                            ecs_meta_set_bool(&cur, field);
                        }
                    }
                    else if (ecs_id(ecs_f32_t) == field_type)
                    {
                        float field = (float)ecs_meta_get_float(&cur);
                        if (igInputFloat("", &field, 0.1f, 1.0f, NULL, 0))
                        {
                            ecs_meta_set_float(&cur, field);
                        }
                    }
                    else if (ecs_id(ecs_u8_t) == field_type)
                    {
                        int64_t field = (float)ecs_meta_get_int(&cur);
                        if (igInputInt("", &field, 1, 2, 0))
                        {
                            ecs_meta_set_int(&cur, field);
                        }
                    }
                    else if (pEcsComponent_GetId(COMPONENT_ID_VEC2_T) == field_type)
                    {
                        vec2_t *field = (vec2_t *)ecs_meta_get_ptr(&cur);
                        float field_v[2] = {field->x, field->y};
                        if (igInputFloat2("", &field_v, NULL, 0))
                        {
                            field->x = field_v[0];
                            field->y = field_v[1];
                        }
                    }
                    else if (pEcsComponent_GetId(COMPONENT_ID_COLOR_T) == field_type)
                    {
                        color_t *field = (color_t *)ecs_meta_get_ptr(&cur);
                        float field_v[4] = {field->r / 255, field->g / 255, field->b / 255, field->a / 255};
                        if (igColorEdit4("", &field_v, 0))
                        {
                            field->r = field_v[0] * 255;
                            field->g = field_v[1] * 255;
                            field->b = field_v[2] * 255;
                            field->a = field_v[3] * 255;
                        }
                    }
                }
                inspector_field_end();
                ecs_meta_next(&cur);
            }
            ecs_meta_pop(&cur);

            igTreePop();
        }
    }
}
