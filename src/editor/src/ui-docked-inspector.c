#include "ui-docked-inspector.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"
#include "pixel/pixel-struct.h"
#include "pixel/pixel-meta-struct.h"
#include "pixel/pixel-components.h"
#include "single-file.h"
#include "utility/string_fn.h"
#include "utility/file_fn.h"
#include "utility/path_fn.h"

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
            const ecs_type_t *type = pEcs_EntityGetType(selected);

            // fix-bug: Cuando tenias una entidad padre con x componentes
            // los hijos repetian el primer componente por defecto la misma
            // cantidad. (type->count-1)
            for (uint32_t i = (type->count - 1); i <= type->count; i--)
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
                    igOpenPopup_Str("inspector-list-components", 0);
                }
                if (igBeginPopup("inspector-list-components", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysUseWindowPadding))
                {
                    const char *componets[] = {pEcsComponent_GetListStr};
                    int index = 0;
                    while (1)
                    {
                        const char *name = componets[index];
                        if (name == NULL)
                            break;
                        if (igMenuItem_Bool(name, NULL, false, true))
                        {
                            pEcsComponent_SetEmptyByString(single->entity_selected, name);
                        }
                        index++;
                    }
                    igEndPopup();
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
    if (!pEcs_EntityIsValid(component))
        return;

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
                        char buffer[32];
                        sprintf(buffer, "%s",field);
                        if (igInputText("", &buffer, MAX_INPUT_TEXT, ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
                        {
                            fflush(stdin);
                            if (strcmp(buffer, "Root") && strcmp(field, "Root") != 0 && strcmp(buffer,"")!=0)
                                ecs_meta_set_string(&cur, buffer);
                        }
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
                    else if (component_id(vec2_t) == field_type)
                    {
                        vec2_t *field = (vec2_t *)ecs_meta_get_ptr(&cur);
                        float field_v[2] = {field->x, field->y};
                        if (igInputFloat2("", &field_v, NULL, 0))
                        {
                            field->x = field_v[0];
                            field->y = field_v[1];
                        }
                    }
                    else if (component_id(color_t) == field_type)
                    {
                        color_t *field = (color_t *)ecs_meta_get_ptr(&cur);
                        float field_v[4] = {field->r, field->g, field->b, field->a};
                        if (igColorEdit4("", &field_v, 0))
                        {
                            field->r = field_v[0];
                            field->g = field_v[1];
                            field->b = field_v[2];
                            field->a = field_v[3];
                        }
                    }
                    else if (component_id(texture_t) == field_type)
                    {
                        texture_t t;
                        texture_t *field = (texture_t *)ecs_meta_get_ptr(&cur);
                        t.id = field->id == 0 ? pResource_GetIconId(RESOUCE_ICON_NO_TEXTURE) : field->id;
                        igImage((ImTextureID){t.id}, (ImVec2){64, 64}, (ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){1, 1, 1, 1}, (ImVec4){0.5f, 0.5f, 0.8f, 1});

                        if (igBeginDragDropTarget())
                        {
                            ImGuiPayload *pay = igAcceptDragDropPayload("browser_file_drag", ImGuiDragDropFlags_SourceNoDisableHover);
                            if (pay)
                            {
                                FileDirFile *file = pay->Data;
                                texture_t t01 = pTexture_LoadFile(PathBuild(file->path, file->filename, NULL));
                                field->id = t01.id;
                                field->width = t01.width;
                                field->height = t01.height;
                                igEndDragDropTarget();
                            }
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
