#include "ui-docked-hierarchy.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"

// Test Test
static ecs_entity_t selected_entity;
static ecs_entity_t cscenetransform;
static bool bHasRoot = false;

// TreeNode SelectedFrags
static ImGuiTreeNodeFlags flag_selected_default = ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_FramePadding;

static void hierarchy_menu_context_open(const char *name, ecs_entity_t e);
static void hierarchy_show_entitys_world(ecs_entity_t t);

void editor_gui_hierarchy_init(void)
{
    cscenetransform = pEcs_EntityLookupByName("ComponentSceneTransform");
}

void editor_gui_hierarchy_draw(void)
{
    if (igBegin("Scene Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0, 0);
        if (igSmallButton("New entity"))
        {
            ecs_entity_t t = pEcs_EntityNew();

            ecs_entity_t parent = (selected_entity > 0 ? selected_entity : pEcs_EntityRoot());
            pEcs_EntitySetParent(parent, t);
        }
        igSeparator();

        /**
         *
         * Cargamos la lista de entidades que se encuentran en el root-entity
         */
        hierarchy_show_entitys_world(pEcs_EntityRoot());
    }
    igEnd();
}

/**
 *
 * Cargamos la lista de entidades que se encuentran en el root-entity
 */
void hierarchy_show_entitys_world(ecs_entity_t entity)
{
    if (pEcs_EntityIsValid(entity))
    {

        const char *entity_name = pEcs_EntityGetName(entity);

        bool bentity_selected = selected_entity == entity ? true : false;
        bool bIsParent = pEcs_EntityIsParent(entity);

        bHasRoot = strcmp(entity_name, "Root") == 0;

        if (bIsParent == false)
        {
            igPushID_Int((int)entity);
            {
                if (igSelectable_Bool(entity_name, bentity_selected, flag_selected_default, (ImVec2){0}))
                {
                    selected_entity = entity;
                }
                hierarchy_menu_context_open(entity_name, entity);
            }
            igPopID();
        }
        else
        {

            ImGuiTreeNodeFlags flags = flag_selected_default;
            flags |= bentity_selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_OpenOnArrow;

            // Siempre que sea el Root estara abrido.
            if (bHasRoot)
            {
                flags |= ImGuiTreeNodeFlags_DefaultOpen;
            }

            bool bopened_treenode = igTreeNodeEx_Str(entity_name, flags);

            //
            if (igIsItemClicked(ImGuiMouseButton_Left))
            {
                selected_entity = entity;
            }

            hierarchy_menu_context_open(entity_name, entity);

            // Ahora buscamos todos los hijos de entity.
            // Pero esto debe tener un requisito, no podemos
            // obtenerlos todos todos... Debemos obtener solo los
            // que tenemos en la escena.

            // Requisitos:
            //  1 - EcsDisabled
            //  2 - Parent
            //  3 - ComponentSceneTransform (Registrar)
            if (bopened_treenode)
            {
                ecs_query_t *query = pEcs_Query(&(ecs_query_desc_t){
                    .filter.terms = {
                        {.id = cscenetransform, .inout = EcsIn},
                        {.id = pEcs_EntityGetParent(entity)},
                        {.id = EcsDisabled, .oper = EcsOptional},
                    }});

                ecs_iter_t it = pEcs_QueryIter(query);
                while (pEcs_QueryIterNext(&it))
                {
                    for (int i = 0; i < it.count; i++)
                    {
                        hierarchy_show_entitys_world(it.entities[i]);
                    }
                }

                pEcs_QueryFree(query);
                igTreePop();
            }
        }
    }
}

/**
 *
 * MenuContext
 *
 * Cuando tenemos una entidad seleccionada podemos abrir este menuContext.
 *
 */
void hierarchy_menu_context_open(const char *name, ecs_entity_t e)
{
    if (bHasRoot)
        return;

    if (igIsItemClicked(ImGuiMouseButton_Right))
    {
        igOpenPopup_Str("hierarchy-menu-context", 0);
    }

    if (igBeginPopupContextItem("hierarchy-menu-context", ImGuiPopupFlags_MouseButtonRight))
    {
        selected_entity = e;
        igText("Entity ( %s )", name);
        igSeparator();

        if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
        {
            pEcs_EntityDelete(selected_entity);
            selected_entity = pEcs_EntityRoot();
        }
        if (igSelectable_Bool("Rename", false, 0, (ImVec2){0, 0}))
        {
        }
        if (selected_entity > 0)
        {
            igSeparator();
            if (igSelectable_Bool("Duplicate", false, 0, (ImVec2){0, 0}))
            {
                pEcs_EntityClone(selected_entity);
            }
        }
        igEndPopup();
    }
}